#include "ViewStates/DisplayDatabaseView.hpp"

#include <functional>
#include <string>

#include <ncurses.h>
#include <ncursesw/form.h>
#include <ncursesw/menu.h>

#include <Helpers/NcursesPrintHelpers.hpp>
#include <SqlDatabase.hpp>
#include <TextFields.hpp>
#include <TuiView.hpp>
#include <ViewStates/ViewStateFactory.hpp>

using namespace tracker::helpers;
using tracker::text_fields::DISPLAY_MENU;

static int TITLE_BAR_HEIGHT = 3;
static int LEFT_OFFSET = 1;
static int BORDER_WIDTH = 1;
static int BORDER_OFFSET = 2 * BORDER_WIDTH;
static int BOTTOM_BORDER_WIDTH = 1;
static int Y_USED_SPACE = TITLE_BAR_HEIGHT + BOTTOM_BORDER_WIDTH;

namespace tracker::view::state
{
DisplayDatabaseView::DisplayDatabaseView(const ViewStateFactory &viewStateFactory) : viewStateFactory(viewStateFactory)
{
    setStateEnum(State::Display);
    winSize = Size(20, 60);

    items = (ITEM **)calloc(26, sizeof(ITEM *));

    items[25] = (ITEM *)NULL;
    menu = new_menu(items);

    window = newwin(winSize.y, winSize.x, scrSize.centeredYBy(winSize), scrSize.centeredXBy(winSize));
    keypad(window, TRUE);
    set_menu_win(menu, window);
    mvwprintw(window, 4, 2, "DATE\tDESCRIPTION\tVALUE");
    set_menu_sub(menu, derwin(window, winSize.y - 6, 38, 5, 1));
    menu_opts_off(menu, O_SHOWDESC);
    menuBox(window, winSize);
    const auto &title = DISPLAY_MENU.title;
    mvwprintw(window, 1, (winSize.x - title.length()) / 2, "%s", title.c_str());

    ITEM **subItems = (ITEM **)calloc(3, sizeof(ITEM *));
    subItems[0] = new_item("BACK", "");
    subItems[1] = new_item("DELETE", "");
    subItems[2] = (ITEM *)NULL;
    operationMenu = new_menu(subItems);
    set_menu_win(operationMenu, window);
    set_menu_sub(operationMenu, derwin(window, 1, winSize.x - 2, 3, 1));
    set_menu_format(operationMenu, 1, 2);
}

std::shared_ptr<IViewState> DisplayDatabaseView::nextState([[maybe_unused]] TuiView &view)
{
    const auto x = view.model->select();
    const auto dataRows = x->getRows();
    delete x;

    std::vector<std::string> strRows;
    for (size_t i = 0; i < dataRows.size(); ++i)
    {
        strRows.push_back(dataRows[i].date + "    " + dataRows[i].name + "    " + std::to_string(dataRows[i].cash));
    }

    for (size_t i = 0; i < dataRows.size(); ++i)
    {
        items[i] = new_item(strRows[i].c_str(), "");
    }
    set_menu_items(menu, items);
    set_menu_format(menu, winSize.y - 6, 1);

    wclear(stdscr);
    refresh();
    post_menu(menu);
    post_menu(operationMenu);
    wrefresh(window);

    int c;
    while ((c = getch()) != KEY_F(1))
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(operationMenu, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(operationMenu, REQ_RIGHT_ITEM);
                break;
            case 10:
                ITEM *curr = current_item(operationMenu);
                const auto &name = item_name(curr);
                if (name == std::string("BACK"))
                {
                    return viewStateFactory.createMenuViewState();
                }
                break;
        }
        wrefresh(window);
    }

    return viewStateFactory.createExitViewState();
}

DisplayDatabaseView::~DisplayDatabaseView()
{
    free_menu(menu);
    for (int i = 0; i < DISPLAY_MENU.size; ++i) free_item(items[i]);

    endwin();
}

}  // namespace tracker::view::state
