#include "ViewStates/ExitViewState.hpp"

#include <ViewStates/ViewStateFactory.hpp>
#include <TuiView.hpp>

namespace tracker::view::state
{

ExitViewState::ExitViewState(const ViewStateFactory& viewStateFactory) : viewStateFactory(viewStateFactory)
{
    state = State::Exit;
}

void ExitViewState::render(TuiView& view) { view.changeState(viewStateFactory.createExitViewState()); }

}  // namespace tracker::view::state
