#include <ncurses.h>

#include <TuiView.hpp>
#include <memory>
#include <string>

namespace tracker::view {
TuiView::TuiView(std::shared_ptr<controller::TuiController> controller, std::shared_ptr<database::SqlDatabase> model)
    : controller(controller), model(model), viewStateFactory(std::make_shared<state::ViewStateFactory>()) {
    initscr();
    start_color();
    use_default_colors();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
}

void TuiView::initDisplayLoop() {
    viewState = viewStateFactory->createMenuViewState();
    while (viewState->getState() != state::State::Exit) {
        viewState = viewState->nextState(*this);
    }
}

TuiView::~TuiView() { endwin(); }
}  // namespace tracker::view
