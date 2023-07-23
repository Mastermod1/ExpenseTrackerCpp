#include <cstdint>
#include <ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ViewStates/ViewStateBuilder.hpp>
#include <string>
#include <Helpers/NcursesPrintHelpers.hpp>

using tracker::helpers::mvprintw;

namespace tracker::view::state
{
InsertViewState::InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) 
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Insert);
}

struct size
{
    int y = 0;
    int x = 0;

    int centeredXBy(const size& s)
    {
	return (x - s.x)/2;
    }

    int centeredYBy(const size& s)
    {
	return (y - s.y)/2;
    }
};

std::shared_ptr<IViewState> InsertViewState::nextState()
{
    wclear(stdscr);
    WINDOW* window;
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int i;
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    my_items = (ITEM **)calloc(fieldCount + 1, sizeof(ITEM *));
    for(i = 0; i < fieldCount; ++i)
	my_items[i] = new_item(fields[i].text.c_str(), "");
    my_items[fieldCount] = (ITEM *)NULL;
    my_menu = new_menu((ITEM **)my_items);
    size wSize{10, 40};
    size sSize{height, width};

    window = newwin(wSize.y, wSize.x, sSize.centeredYBy(wSize), sSize.centeredXBy(wSize));
    keypad(window, TRUE);

    set_menu_win(my_menu, window);
    set_menu_sub(my_menu, derwin(window, 6, 38, 3, 1));

    box(window, 0, 0);
    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, 38);
    mvwaddch(window, 2, 39, ACS_RTEE);

    refresh();

    post_menu(my_menu);
    wrefresh(window);

    while((c = getch()) != KEY_F(1))
    { 
	switch(c)
	{ 
	    case KEY_DOWN:
		menu_driver(my_menu, REQ_DOWN_ITEM);
		break;
	    case KEY_UP:
		menu_driver(my_menu, REQ_UP_ITEM);
		break;
	    case 10:
		ITEM* curr;
		curr = current_item(my_menu);
		const auto& name = item_name(curr);
		mvprintw(0, 0, name);
		if(name == fields.back().text)
		{
		    mvprintw(1, 0, std::string("XDDD").c_str());
		    return viewStateFactory.createMenuViewState();
		}

		    
	}
	wrefresh(window);
    }
    unpost_menu(my_menu);
    free_menu(my_menu);
    for(i = 0; i < fieldCount; ++i)
	free_item(my_items[i]);
    
    endwin();
    return viewStateFactory.createExitViewState();
}
}
