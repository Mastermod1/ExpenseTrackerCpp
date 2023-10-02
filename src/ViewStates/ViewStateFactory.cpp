#include "ViewStates/ViewStateFactory.hpp"

namespace tracker::view::state
{
MenuViewStatePtr ViewStateFactory::createMenuViewState() const { return std::make_shared<MenuViewState>(*this); }

InsertViewStatePtr ViewStateFactory::createInsertViewState() const { return std::make_shared<InsertViewState>(*this); }

DisplayDatabaseViewPtr ViewStateFactory::createDisplayDatabaseView() const
{
    return std::make_shared<DisplayDatabaseView>(*this);
}

ExitViewStatePtr ViewStateFactory::createExitViewState() const { return std::make_shared<ExitViewState>(*this); }
}  // namespace tracker::view::state
