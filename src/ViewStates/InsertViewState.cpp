#include <functional>
#include <ncurses.h>
#include <ViewStates/ViewStateBuilder.hpp>
#include <string>
#include <Helpers/NcursesPrintHelpers.hpp>
#include <ncursesw/form.h>
#include <ncursesw/menu.h>
#include <Helpers/Size.hpp>
#include <TextFields.hpp>

using namespace tracker::helpers;
using tracker::text_fields::INSERT_MENU;

namespace tracker::view::state
{
InsertViewState::InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) 
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Insert);
    scrSize = std::make_shared<Size>(height, width);
    winSize = std::make_shared<Size>(10, 40);

    items = (ITEM**)calloc(INSERT_MENU.size + 1, sizeof(ITEM*));
    for(int i = 0; i < INSERT_MENU.size; ++i)
	items[i] = new_item(INSERT_MENU.fields[i].c_str(), "");
    items[fieldCount] = (ITEM*)NULL;
    menu = new_menu((ITEM**)items);
    window = newwin(winSize->y, winSize->x, scrSize->centeredYBy(*winSize), scrSize->centeredXBy(*winSize));
    keypad(window, TRUE);
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, 6, 38, 3, 1));
    menuBox(window);
}

std::shared_ptr<IViewState> InsertViewState::nextState()
{
    wclear(stdscr);
    refresh();

    post_menu(menu);
    const auto& title = INSERT_MENU.title;
    mvwprintw(window, 1, (winSize->x - title.length())/2, "%s",title.c_str());
    wrefresh(window);

    int c;
    while((c = getch()) != KEY_F(1))
    { 
	switch(c)
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

		if (name == INSERT_MENU.fields.back())
		{
		    return viewStateFactory.createMenuViewState();
		}
	}
	wrefresh(window);
    }

    return viewStateFactory.createExitViewState();
}

InsertViewState::~InsertViewState()
{
    free_menu(menu);
    for (int i = 0; i < INSERT_MENU.size; ++i)
	free_item(items[i]);

    endwin();
}

}
