#pragma once

#include <ncurses.h>

namespace tracker::ncurses::window_wrapper
{
class WindowWrapper
{
   public:
    WindowWrapper(int y, int x, int startY, int startX);

    operator WINDOW*();

    // operator WINDOW**() { return &impl; }

    ~WindowWrapper();

   private:
    WINDOW* impl;
};
}  // namespace tracker::ncurses::window_wrapper
