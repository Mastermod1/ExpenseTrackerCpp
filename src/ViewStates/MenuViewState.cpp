#include "ViewStates/MenuViewState.hpp"

#include <functional>

#include <ncurses.h>
#include <ncursesw/menu.h>

#include <Helpers/NcursesPrintHelpers.hpp>
#include <TextFields.hpp>
#include <TuiView.hpp>
#include <ViewStates/ViewStateFactory.hpp>

using namespace tracker::helpers;
using tracker::text_fields::MAIN_MENU;

namespace tracker::view::state
{
MenuViewState::MenuViewState(const ViewStateFactory& viewStateFactory) : viewStateFactory(viewStateFactory)
{
    state = State::Menu;
    winSize = Size(10, 40);

    items = (ITEM**)calloc(MAIN_MENU.size + 1, sizeof(ITEM*));
    for (int i = 0; i < MAIN_MENU.size; ++i) items[i] = new_item(MAIN_MENU.fields[i].c_str(), "");
    items[MAIN_MENU.size] = (ITEM*)NULL;
    menu = new_menu((ITEM**)items);

    window = newwin(winSize.y, winSize.x, scrSize.centeredYBy(winSize), scrSize.centeredXBy(winSize));
    keypad(window, TRUE);
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, 6, 38, 3, 1));
    menuBox(window, winSize);
    const auto& title = MAIN_MENU.title;
    mvwprintw(window, 1, (winSize.x - title.length()) / 2, "%s", title.c_str());
}

void MenuViewState::render(TuiView& view)
{
    wclear(stdscr);
    refresh();
    post_menu(menu);
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
            case 10:
                ITEM* curr = current_item(menu);
                const auto& name = item_name(curr);

                if (name == MAIN_MENU.fields[0])
                {
                    view.changeState(viewStateFactory.createInsertViewState());
                    return;
                }

                if (name == MAIN_MENU.fields[1])
                {
                    view.changeState(viewStateFactory.createDisplayDatabaseView());
                    return;
                }

                if (name == MAIN_MENU.fields.back())
                {
                    view.changeState(viewStateFactory.createExitViewState());
                    return;
                }
                break;
        }
        wrefresh(window);
    }
}

MenuViewState::~MenuViewState()
{
    free_menu(menu);
    for (int i = 0; i < MAIN_MENU.size; ++i) free_item(items[i]);

    endwin();
}
}  // namespace tracker::view::state
