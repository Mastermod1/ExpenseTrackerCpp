#pragma once

#include <Helpers/Size.hpp>
#include <memory>

namespace tracker::view {
class TuiView;
}  // namespace tracker::view

namespace tracker::view::state {
enum State { None, Menu, Insert, Display, Exit };

class IViewState {
   public:
    virtual std::shared_ptr<IViewState> nextState(TuiView& view) = 0;

    virtual State getState() { return state; }

    virtual void setStateEnum(const State s) { state = s; }

    virtual ~IViewState() = default;

   protected:
    State state = State::None;
    helpers::Size winSize{0, 0};
    helpers::Size scrSize{0, 0};
};

using IViewStatePtr = std::shared_ptr<IViewState>;
}  // namespace tracker::view::state
