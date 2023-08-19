#include <functional>
#include <ncurses.h>
#include <ViewStates/ViewStateBuilder.hpp>
#include <string>
#include <Helpers/NcursesPrintHelpers.hpp>
#include <ncursesw/form.h>
#include <ncursesw/menu.h>
#include <Helpers/Size.hpp>
#include <TextFields.hpp>
#include <TuiView.hpp>
#include <SqlDatabase.hpp>

using namespace tracker::helpers;
using tracker::text_fields::INSERT_MENU;

static int TITLE_BAR_HEIGHT = 3;
static int LEFT_OFFSET = 1;
static int BORDER_WIDTH = 1;
static int BORDER_OFFSET = 2 * BORDER_WIDTH;
static int BOTTOM_BORDER_WIDTH = 1;
static int Y_USED_SPACE = TITLE_BAR_HEIGHT + BOTTOM_BORDER_WIDTH;


namespace tracker::view::state
{
InsertViewState::InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) 
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Insert);
    scrSize = std::make_shared<Size>(height, width);
    winSize = std::make_shared<Size>(20, 60);

    int menuFieldCount = INSERT_MENU.size * 2 - 1;
    formFields = (FIELD**)calloc(menuFieldCount + 1, sizeof(FIELD*));
    int fieldName = 0;
    for(int i = 0; i < menuFieldCount; ++i)
    {
	formFields[i] = new_field(1, winSize->x - 4, i, 1, 0, 0);
	field_opts_off(formFields[i], O_AUTOSKIP);
	if ((i + 1)%2 == 1)
	{
	    set_field_buffer(formFields[i], 0, INSERT_MENU.fields[fieldName].c_str());
	    field_opts_off(formFields[i], O_EDIT);
	    set_field_back(formFields[i], A_NORMAL);
	    fieldName++;
	}
	else
	{
	    set_field_back(formFields[i], A_UNDERLINE);
	}
    }
    form = new_form(formFields);


    int rows, cols;
    scale_form(form, &rows, &cols);
    window = newwin(winSize->y, winSize->x, scrSize->centeredYBy(*winSize), scrSize->centeredXBy(*winSize));
    keypad(window, TRUE);
    set_form_win(form, window);
    set_form_sub(form, derwin(window, winSize->y - Y_USED_SPACE, winSize->x - BORDER_OFFSET, TITLE_BAR_HEIGHT, LEFT_OFFSET));
    menuBox(window, winSize);
    const auto& title = INSERT_MENU.title;
    mvwprintw(window, 1, (winSize->x - title.length())/2, "%s",title.c_str());
}

std::shared_ptr<IViewState> InsertViewState::nextState(TuiView& view)
{
    wclear(stdscr);
    refresh();
    post_form(form);
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
	    case KEY_BACKSPACE:
		form_driver(form, REQ_LEFT_CHAR);
		form_driver(form, REQ_DEL_CHAR);
		break;	
	    case 10:
	    {
		FIELD* curr = current_field(form);
		const auto& name = trim_whitespaces(field_buffer(curr, 0));
		if (name == INSERT_MENU.fields.back())
		{
		    return viewStateFactory.createMenuViewState();
		}
		if (name == INSERT_MENU.fields[INSERT_MENU.size - 2])
		{
		    std::string values = "NULL, '";
		    values += trim_whitespaces(field_buffer(formFields[3], 0)); // date
		    values += "', '";
		    values += trim_whitespaces(field_buffer(formFields[1], 0)); // desc
		    values += "', ";
		    values += trim_whitespaces(field_buffer(formFields[5], 0)); // value

		    if(view.model->insert(values))
			mvwprintw(window, winSize->y - 2, 1, "Status: %s", "SUCCESS");
		}
		break;
	    }
	    default:
		form_driver(form, c);
		break;	
	}
	wrefresh(window);
    }

    return viewStateFactory.createExitViewState();
}

InsertViewState::~InsertViewState()
{
    free_form(form);
    for (int i = 0; i < INSERT_MENU.size * 2; ++i)
	free_field(formFields[i]);

    endwin();
}

}
