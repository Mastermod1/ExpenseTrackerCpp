#include <ncurses.h>
#include <ncursesw/menu.h>

#include <Helpers/NcursesPrintHelpers.hpp>
#include <Helpers/Size.hpp>
#include <IViewState.hpp>
#include <TextFields.hpp>
#include <functional>

#include "ViewStates/ViewStateBuilder.hpp"

using namespace tracker::helpers;
using tracker::text_fields::MAIN_MENU;

namespace tracker::view::state {
MenuViewState::MenuViewState(const ViewStateFactory& viewStateFactory, int height, int width)
    : viewStateFactory(viewStateFactory), height(height), width(width) {
    setStateEnum(State::Menu);
    scrSize = std::make_shared<Size>(height, width);
    winSize = std::make_shared<Size>(10, 40);

    items = (ITEM**)calloc(MAIN_MENU.size + 1, sizeof(ITEM*));
    for (int i = 0; i < MAIN_MENU.size; ++i) items[i] = new_item(MAIN_MENU.fields[i].c_str(), "");
    items[MAIN_MENU.size] = (ITEM*)NULL;
    menu = new_menu((ITEM**)items);

    window = newwin(winSize->y, winSize->x, scrSize->centeredYBy(*winSize), scrSize->centeredXBy(*winSize));
    keypad(window, TRUE);
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, 6, 38, 3, 1));
    menuBox(window, winSize);
    const auto& title = MAIN_MENU.title;
    mvwprintw(window, 1, (winSize->x - title.length()) / 2, "%s", title.c_str());
}

std::shared_ptr<IViewState> MenuViewState::nextState([[maybe_unused]] TuiView& view) {
    wclear(stdscr);
    refresh();
    post_menu(menu);
    wrefresh(window);

    int c;
    while ((c = getch()) != KEY_F(1)) {
        switch (c) {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;
            case 10:
                ITEM* curr = current_item(menu);
                const auto& name = item_name(curr);

                if (name == MAIN_MENU.fields[0]) {
                    return viewStateFactory.createInsertViewState();
                }

                if (name == MAIN_MENU.fields[1]) {
                    return viewStateFactory.createDisplayDatabaseView();
                }

                if (name == MAIN_MENU.fields.back()) {
                    return viewStateFactory.createExitViewState();
                }
                break;
        }
        wrefresh(window);
    }

    return viewStateFactory.createExitViewState();
}

MenuViewState::~MenuViewState() {
    free_menu(menu);
    for (int i = 0; i < MAIN_MENU.size; ++i) free_item(items[i]);

    endwin();
}
}  // namespace tracker::view::state
