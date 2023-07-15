#pragma once

#include "ViewStates/ViewStateBuilder.hpp"
#include <memory>
#include <IViewState.hpp>

namespace tracker::database
{
    class SqlDatabase;
}  // namespace tracker::database

namespace tracker::controller
{
    class TuiController;
}  // namespace tracker::controller

namespace tracker::view
{
class TuiView
{
public:
    TuiView(
        std::shared_ptr<controller::TuiController> controller,
        std::shared_ptr<database::SqlDatabase> model);

    void initDisplayLoop();
    void handleControls();

    ~TuiView();
    
private:
    std::shared_ptr<controller::TuiController> controller;
    std::shared_ptr<database::SqlDatabase> model;
    state::IViewStatePtr viewState;
    state::ViewStateFactoryPtr viewStateFactory;
    int keyState = 0;
    int width = 0;
    int height = 0;
};

}  // namespace tracker::view
