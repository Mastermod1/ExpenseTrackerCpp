#include "ViewStates/InsertViewState.hpp"

#include <functional>
#include <string>

#include <ncurses.h>
#include <ncursesw/form.h>
#include <ncursesw/menu.h>

#include <Helpers/NcursesPrintHelpers.hpp>
#include <Ncurses/WindowWrapper.hpp>
#include <SqlDatabase.hpp>
#include <TextFields.hpp>
#include <TuiView.hpp>
#include <ViewStates/ViewStateFactory.hpp>

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
InsertViewState::InsertViewState(const ViewStateFactory &viewStateFactory)
    : viewStateFactory(viewStateFactory),
      window(20, 60, scrSize.centeredYBy(Size(20, 60)), scrSize.centeredXBy(Size(20, 60)))
{
    state = State::Insert;

    formFields = (FIELD **)calloc(INSERT_MENU.size + 1, sizeof(FIELD *));
    for (int i = 0; i < INSERT_MENU.size - 2; ++i)
    {
        formFields[i] = new_field(1, winSize.x - 4, i * 2 + 1, 1, 0, 0);
        field_opts_off(formFields[i], O_AUTOSKIP);
        set_field_back(formFields[i], A_UNDERLINE);
    }

    formFields[3] = new_field(1, winSize.x - 4, 3 * 2, 1, 0, 0);
    set_field_buffer(formFields[3], 0, INSERT_MENU.fields[3].c_str());
    formFields[4] = new_field(1, winSize.x - 4, 3 * 2 + 1, 1, 0, 0);
    set_field_buffer(formFields[4], 0, INSERT_MENU.fields[4].c_str());

    form = new_form(formFields);

    int rows, cols;
    scale_form(form, &rows, &cols);
    keypad(window, TRUE);
    set_form_win(form, window);
    set_form_sub(form,
                 derwin(window, winSize.y - Y_USED_SPACE, winSize.x - BORDER_OFFSET, TITLE_BAR_HEIGHT, LEFT_OFFSET));
    menuBox(window, winSize);
    const auto &title = INSERT_MENU.title;
    mvwprintw(window, 1, (winSize.x - title.length()) / 2, "%s", title.c_str());
}

void InsertViewState::render(TuiView &view)
{
    wclear(stdscr);
    refresh();
    post_form(form);
    mvwprintw(window, 0 * 2 + 3, 2, INSERT_MENU.fields[0]);
    mvwprintw(window, 1 * 2 + 3, 2, INSERT_MENU.fields[1]);
    mvwprintw(window, 2 * 2 + 3, 2, INSERT_MENU.fields[2]);
    wmove(window, 4, 2);
    wrefresh(window);

    int c;
    while ((c = getch()) != KEY_F(1))
    {
        switch (c)
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
                FIELD *curr = current_field(form);
                const auto &name = trim_whitespaces(field_buffer(curr, 0));
                if (name == INSERT_MENU.fields.back())
                {
                    view.changeState(viewStateFactory.createMenuViewState());
                    return;
                }
                if (name == INSERT_MENU.fields[3])
                {
                    std::string values = "NULL, '";
                    values += trim_whitespaces(field_buffer(formFields[0], 0));  // date
                    values += "', '";
                    values += trim_whitespaces(field_buffer(formFields[1], 0));  // desc
                    values += "', ";
                    values += trim_whitespaces(field_buffer(formFields[2], 0));  // value

                    mvwprintw(window, winSize.y - 2, 1, "Status: %s",
                              view.model->insert(values) ? "SUCCESS" : "FAILED");
                }
                break;
            }
            default:
                form_driver(form, c);
                break;
        }
        wrefresh(window);
    }
}

InsertViewState::~InsertViewState()
{
    free_form(form);
    for (int i = 0; i < INSERT_MENU.size + 1; ++i) free_field(formFields[i]);
}

}  // namespace tracker::view::state
