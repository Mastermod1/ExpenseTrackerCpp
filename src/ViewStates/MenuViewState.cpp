#include "ViewStates/ViewStateBuilder.hpp"
#include <IViewState.hpp>
#include <ncurses.h>

namespace tracker::view::state
{
MenuViewState::MenuViewState(
    const ViewStateFactory& viewStateFactory,
    int height,
    int width)
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Menu);
}

void MenuViewState::draw()
{
    wclear(stdscr);
    for(int i = 0; i < 4; i++)
    {
	const auto& field = menuFields[i].c_str();
	if(clampedHighlightPos() == i)
	{
	    wattron(stdscr, A_REVERSE);
	    mvprintw(height/2 + i, width/2, field);
	    wattroff(stdscr, A_REVERSE);
	}
	else
	{
	    mvprintw(height/2 + i, width/2, field);
	}
    }
    // move(0, 0);
    curs_set(0);
}

std::shared_ptr<IViewState> MenuViewState::nextState()
{
    switch(getCursor())
    {
	case 1:
	    return viewStateFactory.createInsertViewState(); 
	case 3:
	    return viewStateFactory.createExitViewState();
	default:
	    return std::make_shared<MenuViewState>(*this);
    }
    return std::make_shared<MenuViewState>(*this);
}

int MenuViewState::clampedHighlightPos()
{
    if(cursor >= 4)
	cursor = 0;
    if(cursor < 0)
	cursor = 3;
    return cursor;
}
}
