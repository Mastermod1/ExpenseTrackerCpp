#include "WindowWrapper.hpp"

#include <ncurses.h>

namespace tracker::ncurses::window_wrapper
{
WindowWrapper::WindowWrapper(int y, int x, int startY, int startX) { impl = newwin(y, x, startY, startX); }

WindowWrapper::operator WINDOW*() { return impl; }

// operator WINDOW**() { return &impl; }

WindowWrapper::~WindowWrapper()
{
    if (impl != nullptr)
    {
        delwin(impl);
    }
}

}  // namespace tracker::ncurses::window_wrapper
