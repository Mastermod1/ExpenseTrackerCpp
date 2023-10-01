#include <ViewStates/ViewStateBuilder.hpp>

namespace tracker::view::state {
ViewStateFactory::ViewStateFactory(int height, int width) : height(height), width(width) {}

MenuViewStatePtr ViewStateFactory::createMenuViewState() const {
    return std::make_shared<MenuViewState>(*this, height, width);
}

InsertViewStatePtr ViewStateFactory::createInsertViewState() const {
    return std::make_shared<InsertViewState>(*this, height, width);
}

DisplayDatabaseViewPtr ViewStateFactory::createDisplayDatabaseView() const {
    return std::make_shared<DisplayDatabaseView>(*this, height, width);
}

ExitViewStatePtr ViewStateFactory::createExitViewState() const { return std::make_shared<ExitViewState>(*this); }
}  // namespace tracker::view::state
