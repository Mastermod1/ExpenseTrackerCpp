#pragma once

#include <curses.h>

#include <IViewState.hpp>
#include <memory>

namespace tracker::view::state {
class ViewStateFactory;

class ExitViewState : public IViewState {
 public:
  ExitViewState(const ViewStateFactory& viewStateFactory)
      : viewStateFactory(viewStateFactory) {
    setStateEnum(State::Exit);
  }

  std::shared_ptr<IViewState> nextState(TuiView& view) override {
    return std::make_shared<ExitViewState>(*this);
  }

 private:
  const ViewStateFactory& viewStateFactory;
};

using ExitViewStatePtr = std::shared_ptr<ExitViewState>;
}  // namespace tracker::view::state
