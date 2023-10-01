#pragma once

#include <ViewStates/DisplayDatabaseView.hpp>
#include <ViewStates/ExitViewState.hpp>
#include <ViewStates/InsertViewState.hpp>
#include <ViewStates/MenuViewState.hpp>
#include <memory>

namespace tracker::view::state {
class ViewStateFactory {
   public:
    ViewStateFactory(int height, int width);

    std::shared_ptr<MenuViewState> createMenuViewState() const;

    std::shared_ptr<InsertViewState> createInsertViewState() const;

    std::shared_ptr<DisplayDatabaseView> createDisplayDatabaseView() const;

    std::shared_ptr<ExitViewState> createExitViewState() const;

   private:
    int height = 0;
    int width = 0;
};

using ViewStateFactoryPtr = std::shared_ptr<ViewStateFactory>;
}  // namespace tracker::view::state
