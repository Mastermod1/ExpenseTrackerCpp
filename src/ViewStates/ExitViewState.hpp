#pragma once

#include <memory>

#include <IViewState.hpp>

namespace tracker::view::state
{
class ViewStateFactory;

class ExitViewState : public IViewState
{
   public:
    ExitViewState(const ViewStateFactory& viewStateFactory);

    void render(TuiView& view) override;

   private:
    const ViewStateFactory& viewStateFactory;
};

using ExitViewStatePtr = std::shared_ptr<ExitViewState>;
}  // namespace tracker::view::state
