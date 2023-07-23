#pragma once

#include <memory>

namespace tracker::view::state
{
enum State{
    None,
    Menu,
    Insert,
    Exit
};

class IViewState
{
public:
    virtual std::shared_ptr<IViewState> nextState() = 0;

    virtual State getState()
    {
	return state;
    }

    virtual void setStateEnum(const State s)
    {
	state = s;
    }

    virtual ~IViewState() = default;

protected:
    State state = State::None;
};

using IViewStatePtr = std::shared_ptr<IViewState>;
}
