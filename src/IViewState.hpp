#pragma once

#include <memory>

#include <ncurses.h>

#include <Helpers/Size.hpp>

namespace tracker::view
{
class TuiView;
}  // namespace tracker::view

namespace tracker::view::state
{
enum State
{
    None,
    Menu,
    Insert,
    Display,
    Exit
};

class IViewState
{
   public:
    IViewState() { getmaxyx(stdscr, scrSize.y, scrSize.x); }

    virtual void render(TuiView& view) = 0;

    virtual State getState() { return state; }

    virtual ~IViewState() = default;

   protected:
    State state = State::None;
    helpers::Size winSize{0, 0};
    helpers::Size scrSize{0, 0};
};

using IViewStatePtr = std::shared_ptr<IViewState>;
}  // namespace tracker::view::state
