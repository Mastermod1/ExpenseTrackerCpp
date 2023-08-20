#pragma once

#include <IViewState.hpp>
#include <ViewStates/DisplayDatabaseView.hpp>
#include <ViewStates/ExitViewState.hpp>
#include <ViewStates/InsertViewState.hpp>
#include <ViewStates/MenuViewState.hpp>
#include <memory>
#include <string>
#include <vector>

namespace tracker::view::state {
class ViewStateFactory {
   public:
    ViewStateFactory(int height, int width) : height(height), width(width) {}

    MenuViewStatePtr createMenuViewState() const { return std::make_shared<MenuViewState>(*this, height, width); }

    InsertViewStatePtr createInsertViewState() const { return std::make_shared<InsertViewState>(*this, height, width); }

    DisplayDatabaseViewPtr createDisplayDatabaseView() const {
        return std::make_shared<DisplayDatabaseView>(*this, height, width);
    }

    ExitViewStatePtr createExitViewState() const { return std::make_shared<ExitViewState>(*this); }

   private:
    int height = 0;
    int width = 0;
};

using ViewStateFactoryPtr = std::shared_ptr<ViewStateFactory>;
}  // namespace tracker::view::state
