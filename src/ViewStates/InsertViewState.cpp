#include <functional>
#include <ncurses.h>
#include <ViewStates/ViewStateBuilder.hpp>
#include <string>
#include <Helpers/NcursesPrintHelpers.hpp>
#include <ncursesw/form.h>
#include <ncursesw/menu.h>
#include <Helpers/Size.hpp>
#include <TextFields.hpp>
#include <string.h>

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
    items[INSERT_MENU.size] = (ITEM*)NULL;
    menu = new_menu((ITEM**)items);

    window = newwin(winSize->y, winSize->x, scrSize->centeredYBy(*winSize), scrSize->centeredXBy(*winSize));
    keypad(window, TRUE);
    set_menu_win(menu, window);
    set_menu_sub(menu, derwin(window, 6, 38, 3, 1));
    menuBox(window);

    formFields = (FIELD**)calloc(4, sizeof(FIELD*));
    for(int i = 0; i < 4; ++i)
    {
	formFields[i] = new_field(1, 10, 4 + 2*i, 18, 0, 0);
	set_field_back(formFields[i], A_UNDERLINE);
	field_opts_off(formFields[i], O_AUTOSKIP);
    }
    set_field_buffer(formFields[3], 0, INSERT_MENU.fields.back().c_str());
    field_opts_off(formFields[3], O_EDIT);
    set_field_back(formFields[3], A_NORMAL);
    form = new_form(formFields);
}

static char* trim_whitespaces(char *str)
{
	char *end;

	// trim leading space
	while(isspace(*str))
		str++;

	if(*str == 0) // all spaces?
		return str;

	// trim trailing space
	end = str + strnlen(str, 128) - 1;

	while(end > str && isspace(*end))
		end--;

	// write new null terminator
	*(end+1) = '\0';

	return str;
}

std::shared_ptr<IViewState> InsertViewState::nextState()
{
    wclear(stdscr);
    refresh();

    // post_menu(menu);
    post_form(form);
    const auto& title = INSERT_MENU.title;
    mvwprintw(window, 1, (winSize->x - title.length())/2, "%s",title.c_str());
    wrefresh(window);

    int c;
    while((c = getch()) != KEY_F(1))
    { 
	switch(c)
	{ 
	    case KEY_DOWN:
		form_driver(form, REQ_NEXT_FIELD);
		form_driver(form, REQ_END_LINE);
		break;
	    case KEY_UP:
		form_driver(form, REQ_PREV_FIELD);
		form_driver(form, REQ_END_LINE);
		break;
	    case 10:
	    {
		FIELD* curr = current_field(form);
		const auto& name = trim_whitespaces(field_buffer(curr, 0));
		mvprintw(0, 0, name);

		if (name == INSERT_MENU.fields.back())
		{
		    mvprintw(1, 0, "EQUAL");
		    return viewStateFactory.createMenuViewState();
		}
		break;
	    }
	    default:
		form_driver(form, c);
		break;	
	 //    case KEY_DOWN:
		// menu_driver(menu, REQ_DOWN_ITEM);
		// break;
	 //    case KEY_UP:
		// menu_driver(menu, REQ_UP_ITEM);
		// break;
	 //    case 10:
		// ITEM* curr = current_item(menu);
		// const auto& name = item_name(curr);
		//
		// if (name == INSERT_MENU.fields.back())
		// {
		//     return viewStateFactory.createMenuViewState();
		// }
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

    free_form(form);
    for (int i = 0; i < 4; ++i)
	free_field(formFields[i]);

    endwin();
}

}
