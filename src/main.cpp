#include <SqlDatabase.hpp>
#include <TuiController.hpp>
#include <memory>

using namespace tracker;

int main() {
  auto model = std::make_shared<database::SqlDatabase>();
  auto controller = std::make_shared<controller::TuiController>(model);

  controller->start();
}
