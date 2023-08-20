#include <TuiController.hpp>

namespace tracker::controller {
TuiController::TuiController(std::shared_ptr<database::SqlDatabase> db)
    : model(db) {
  view = std::make_shared<view::TuiView>(std::make_shared<TuiController>(this),
                                         model);
}

void TuiController::start() { view->initDisplayLoop(); }

TuiController::TuiController(TuiController* other) {
  view = other->view;
  model = other->model;
}
}  // namespace tracker::controller
