#pragma once

#include <string>
#include <memory>

typedef struct _win_st WINDOW;

namespace tracker::helpers
{
class Size;

void mvprintw(int row, int col, const std::string& s);
void menuBox(WINDOW* window, const std::shared_ptr<helpers::Size>& size);
char* trim_whitespaces(char *str);
}
