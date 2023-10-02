#pragma once

#include <memory>
#include <string>

typedef struct _win_st WINDOW;

namespace tracker::helpers
{
class Size;

void mvprintw(int row, int col, const std::string& s);
void mvwprintw(WINDOW* window, int row, int col, const std::string& s);
void menuBox(WINDOW* window, const helpers::Size& size);
char* trim_whitespaces(char* str);
}  // namespace tracker::helpers
