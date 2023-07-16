#include <ncurses.h>
#include <ViewStates/ViewStateBuilder.hpp>
#include <string>
#include <Helpers/NcursesPrintHelpers.hpp>

using tracker::helpers::mvprintw;

namespace tracker::view::state
{
InsertViewState::InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) 
    : viewStateFactory(viewStateFactory), height(height), width(width)
{
    setStateEnum(State::Insert);
}

void InsertViewState::readLine()
{
    std::string line = fields[1].text;
    int key = getch();
    while(key != 10)
    {
	if(key == 66)
	{
	    moveCursor(1);
	    draw();
	    return;
	}
	if(key == 65)
	{
	    moveCursor(-1);
	    draw();
	    return;
	}
	if(key == 127)
	{
	    line = line.substr(0, line.size() - 1);
	}
	else {
	    line += key;
	}
	key = getch();
    }
    fields[1].text = line;
    moveCursor(1);
    draw();
}

void InsertViewState::draw()
{
    wclear(stdscr);
    const auto cursorPos = clampedHighlightPos();
    for(int i = 0; i < fieldCount; i++)
    {
	if(cursorPos == i)
	{
	    wattron(stdscr, A_REVERSE);
	    mvprintw(height/2 + i, width/2, fields[i].text);
	    wattroff(stdscr, A_REVERSE);
	}
	else
	{
	    mvprintw(height/2 + i, width/2, fields[i].text);
	}
    }
    if(cursorPos == 1)
	readLine();
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
