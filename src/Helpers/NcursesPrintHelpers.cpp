#include <Helpers/NcursesPrintHelpers.hpp>

#include <ncurses.h>
#include <string>

namespace tracker::helpers
{
void mvprintw(int row, int col, const std::string& s)
{
    ::mvprintw(row, col, "%s", s.c_str());
}

void menuBox(WINDOW* window)
{
    box(window, 0, 0);
    mvwaddch(window, 2, 0, ACS_LTEE);
    mvwhline(window, 2, 1, ACS_HLINE, 38);
    mvwaddch(window, 2, 39, ACS_RTEE);
}
}
