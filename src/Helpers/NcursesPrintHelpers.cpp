#include <Helpers/NcursesPrintHelpers.hpp>

#include <ncurses.h>
#include <string>

namespace tracker::helpers
{
void mvprintw(int row, int col, const std::string& s)
{
    ::mvprintw(row, col, "%s", s.c_str());
}
}
