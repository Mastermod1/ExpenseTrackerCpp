#pragma once

#include <memory>

#include <SqlDatabase.hpp>
#include <TuiView.hpp>

namespace tracker::controller
{
class TuiController
{
   public:
    TuiController(std::shared_ptr<database::SqlDatabase> db);
    TuiController(TuiController* other);

    void start();

   private:
    std::shared_ptr<view::TuiView> view;
    std::shared_ptr<database::SqlDatabase> model;
};
}  // namespace tracker::controller
