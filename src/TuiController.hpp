#pragma once

#include <TuiView.hpp>
#include <memory>

namespace tracker::database {
class SqlDatabase;
}  // namespace tracker::database

namespace tracker::controller {
class TuiController {
 public:
  TuiController(std::shared_ptr<database::SqlDatabase> db);
  TuiController(TuiController* other);

  void start();

 private:
  std::shared_ptr<view::TuiView> view;
  std::shared_ptr<database::SqlDatabase> model;
};
}  // namespace tracker::controller
