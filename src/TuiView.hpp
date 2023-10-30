#pragma once

#include <memory>

#include <IViewState.hpp>
#include <SqlDatabase.hpp>
#include <ViewStates/ViewStateFactory.hpp>

namespace tracker::controller
{
class TuiController;
}

namespace tracker::view
{
class TuiView
{
   public:
    TuiView(std::shared_ptr<controller::TuiController> controller, std::shared_ptr<database::SqlDatabase> model);

    void initDisplayLoop();
    void handleControls();
    void changeState(state::IViewStatePtr state);

    ~TuiView();

    std::shared_ptr<controller::TuiController> controller;
    std::shared_ptr<database::SqlDatabase> model;

   private:
    state::IViewStatePtr viewState;
    state::ViewStateFactoryPtr viewStateFactory;
};

}  // namespace tracker::view
