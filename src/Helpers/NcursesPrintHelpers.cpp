#include <Helpers/NcursesPrintHelpers.hpp>

#include <ncurses.h>
#include <string.h>
#include <Helpers/Size.hpp>

namespace tracker::helpers
{
void mvprintw(int row, int col, const std::string& s)
{
    ::mvprintw(row, col, "%s", s.c_str());
}

void menuBox(WINDOW* window, const std::shared_ptr<helpers::Size>& size)
{
    box(window, 0, 0);
    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, size->x - 2);
    mvwaddch(window, 2, size->x - 1, ACS_RTEE);
}

char* trim_whitespaces(char *str)
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

}
