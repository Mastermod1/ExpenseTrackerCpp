#pragma once

#include <ncurses.h>
#include <string>

namespace tracker::helpers
{
void mvprintw(int row, int col, const std::string& s);
void menuBox(WINDOW* window);
}
