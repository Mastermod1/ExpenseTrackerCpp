#include <TuiView.hpp>

#include <string>
#include <ncurses.h>

namespace tracker::view
{
TuiView::TuiView(
    std::shared_ptr<controller::TuiController> controller,
    std::shared_ptr<database::SqlDatabase> model)
: controller(controller), model(model)
{
    initscr();
    getmaxyx(stdscr, height, width);
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    // attron(COLOR_PAIR(1));
}

void TuiView::initDisplayLoop()
{
    int key = 0;
    while (key != 'q')
    {
	drawMenu();
	refresh();
	key = getch();
	if (key == 66) // UP
	    highlight++;
	if (key == 65) // DOWN
	    highlight--;
	if (key == 10) // ENTER
	{
	    switch(highlight)
	    {
		case 3:
		    key = 'q';
		    break;
		default:
		    key = '0';
		    break;
	    }
	}

	printw(std::to_string(key).c_str());
	mvprintw(1, 0, std::to_string(highlight).c_str());
    }
}

void TuiView::drawMenu()
{
    for(int i = 0; i < 4; i++)
    {
	if(clampedHighlightPos() == i)
	{
	    wattron(stdscr, A_REVERSE);
	    mvprintw(height/2 + i, width/2, menuFields[i]);
	    wattroff(stdscr, A_REVERSE);
	}
	else
	{
	    mvprintw(height/2 + i, width/2, menuFields[i]);
	}
    }
    move(0, 0);
}

int TuiView::clampedHighlightPos()
{
    if(highlight >= 4)
	highlight = 0;
    if(highlight < 0)
	highlight = 3;
    return highlight;
}

TuiView::~TuiView()
{
    endwin();
}
}  // namespace tracker::view
