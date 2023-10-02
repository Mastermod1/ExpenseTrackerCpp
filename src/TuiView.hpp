#pragma once

#include <IViewState.hpp>
#include <SqlDatabase.hpp>
#include <ViewStates/ViewStateFactory.hpp>
#include <memory>

namespace tracker::controller {
class TuiController;
}

namespace tracker::view {
class TuiView {
   public:
    TuiView(std::shared_ptr<controller::TuiController> controller, std::shared_ptr<database::SqlDatabase> model);

    void initDisplayLoop();
    void handleControls();

    ~TuiView();

    std::shared_ptr<controller::TuiController> controller;
    std::shared_ptr<database::SqlDatabase> model;

   private:
    state::IViewStatePtr viewState;
    std::shared_ptr<state::ViewStateFactory> viewStateFactory;
    int keyState = 0;
};

}  // namespace tracker::view
