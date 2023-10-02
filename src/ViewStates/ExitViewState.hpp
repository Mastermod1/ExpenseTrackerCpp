#pragma once

#include <memory>

#include <IViewState.hpp>

namespace tracker::view::state
{
class ViewStateFactory;

class ExitViewState : public IViewState
{
   public:
    ExitViewState(const ViewStateFactory& viewStateFactory) : viewStateFactory(viewStateFactory)
    {
        setStateEnum(State::Exit);
    }

    std::shared_ptr<IViewState> nextState([[maybe_unused]] TuiView& view) override
    {
        return std::make_shared<ExitViewState>(*this);
    }

   private:
    const ViewStateFactory& viewStateFactory;
};

using ExitViewStatePtr = std::shared_ptr<ExitViewState>;
}  // namespace tracker::view::state
