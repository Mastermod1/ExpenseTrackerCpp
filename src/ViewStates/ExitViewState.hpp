#pragma once

#include <IViewState.hpp>
#include <curses.h>
#include <memory>

namespace tracker::view::state
{
class ViewStateFactory;

class ExitViewState : public IViewState
{
public:
    ExitViewState(const ViewStateFactory& viewStateFactory) : viewStateFactory(viewStateFactory)
    {
	setStateEnum(State::Exit);
    }

    void draw() override { wclear(stdscr); }
    std::shared_ptr<IViewState> nextState() override 
    {
	return std::make_shared<ExitViewState>(*this);
    }

private:
    const ViewStateFactory& viewStateFactory;
};

using ExitViewStatePtr = std::shared_ptr<ExitViewState>;
}
