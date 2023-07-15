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
    viewStateFactory = std::make_shared<state::ViewStateFactory>(height, width);
    // attron(COLOR_PAIR(1));
}

void TuiView::initDisplayLoop()
{
    viewState = viewStateFactory->createMenuViewState();
    while (true)
    {
	if (viewState->getState() == state::State::Exit)
	{
	    break;
	}

	viewState->draw();
	refresh();
	handleControls();
	printw(std::to_string(keyState).c_str());
	mvprintw(1, 0, std::to_string(viewState->getState()).c_str());
    }
}

void TuiView::handleControls()
{
    keyState = getch();
    if (keyState == 66) // UP
	viewState->moveCursor(1);
    if (keyState == 65) // DOWN
	viewState->moveCursor(-1);
    if (keyState == 10) // ENTER
    {
	viewState = viewState->nextState();
    }
}

TuiView::~TuiView()
{
    endwin();
}
}  // namespace tracker::view
