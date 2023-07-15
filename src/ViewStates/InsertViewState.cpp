#include <ncurses.h>
#include <ViewStates/ViewStateBuilder.hpp>

namespace tracker::view::state
{
InsertViewState::InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) 
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Insert);
}

void InsertViewState::draw()
{
    wclear(stdscr);
    for(int i = 0; i < fieldCount; i++)
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

std::shared_ptr<IViewState> InsertViewState::nextState()
{
    switch(getCursor())
    {
        case 2:
	    return viewStateFactory.createMenuViewState();
	default:
	    return std::make_shared<InsertViewState>(*this);
    }
    return std::make_shared<InsertViewState>(*this);
}

int InsertViewState::clampedHighlightPos()
{
    if(cursor >= fieldCount)
	cursor = 0;
    if(cursor < 0)
	cursor = fieldCount - 1;
    return cursor;
}
}
