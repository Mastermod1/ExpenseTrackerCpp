#include "IViewState.hpp"
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
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    viewStateFactory = std::make_shared<state::ViewStateFactory>(height, width);
}

void TuiView::initDisplayLoop()
{
    viewState = viewStateFactory->createMenuViewState();
    while (viewState->getState() != state::State::Exit)
    {
	viewState = viewState->nextState(*this);
    }
}

TuiView::~TuiView()
{
    endwin();
}
}  // namespace tracker::view
