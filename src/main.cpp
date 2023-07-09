#include "DataTypes/Row.hpp"
#include "SqlDatabase.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ncurses.h>
#include <string>

class TuiView
{
public:
    TuiView()
    {
	initscr();
	getmaxyx(stdscr, height, width);
	start_color();
	use_default_colors();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	// attron(COLOR_PAIR(1));
    }

    void initDisplayLoop()
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

    void drawMenu()
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

    int clampedHighlightPos()
    {
	if(highlight >= 4)
	    highlight = 0;
	if(highlight < 0)
	    highlight = 3;
	return highlight;
    }

    ~TuiView()
    {
	endwin();
    }
private:
    int highlight = 0;
    int width = 0;
    int height = 0;
    char* menuFields[4] = {
	"MENU",	
	"ADD ROW",	
	"DISPLAY DATABASE",	
	"EXIT",	
    };
};

int main()
{
    TuiView display;
    display.initDisplayLoop();

    tracker::database::SqlDatabase db;

}
