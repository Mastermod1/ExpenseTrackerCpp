#include "TuiView.hpp"

#include <memory>
#include <string>

#include <NcursesViewSetuper.hpp>

namespace tracker::view
{
TuiView::TuiView(std::shared_ptr<controller::TuiController> controller, std::shared_ptr<database::SqlDatabase> model)
    : controller(controller), model(model), viewStateFactory(std::make_shared<state::ViewStateFactory>())
{
    NcursesViewSetuper::setUp();
}

void TuiView::initDisplayLoop()
{
    viewState = viewStateFactory->createMenuViewState();
    while (viewState->getState() != state::State::Exit)
    {
        viewState->render(*this);
    }
}

void TuiView::changeState(const state::IViewStatePtr state) { viewState = state; }

TuiView::~TuiView() { endwin(); }
}  // namespace tracker::view
