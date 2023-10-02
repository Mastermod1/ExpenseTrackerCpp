#include <NcursesViewSetuper.hpp>

namespace tracker::view
{
void NcursesViewSetuper::setUp()
{
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
}
}  // namespace tracker::view
