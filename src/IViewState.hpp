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
    virtual void draw() = 0;
    virtual std::shared_ptr<IViewState> nextState() = 0;
    virtual State getState()
    {
	return state;
    }
    virtual int getCursor()
    {
	return cursor;
    }
    virtual void moveCursor(int i)
    {
	cursor += i;
    }
    
    virtual void setStateEnum(const State s)
    {
	state = s;
    }

    virtual ~IViewState() = default;
protected:
    State state = State::None;
    int cursor = 0;
};

using IViewStatePtr = std::shared_ptr<IViewState>;
}
