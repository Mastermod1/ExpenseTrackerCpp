#pragma once

#include <ViewStates/DisplayDatabaseView.hpp>
#include <ViewStates/ExitViewState.hpp>
#include <ViewStates/InsertViewState.hpp>
#include <ViewStates/MenuViewState.hpp>
#include <memory>

namespace tracker::view::state {
class ViewStateFactory {
   public:
    std::shared_ptr<MenuViewState> createMenuViewState() const;

    std::shared_ptr<InsertViewState> createInsertViewState() const;

    std::shared_ptr<DisplayDatabaseView> createDisplayDatabaseView() const;

    std::shared_ptr<ExitViewState> createExitViewState() const;
};

using ViewStateFactoryPtr = std::shared_ptr<ViewStateFactory>;
}  // namespace tracker::view::state
