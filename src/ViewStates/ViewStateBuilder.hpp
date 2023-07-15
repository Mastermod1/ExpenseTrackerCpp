#pragma once

#include <ViewStates/ExitViewState.hpp>
#include <ViewStates/MenuViewState.hpp>
#include <ViewStates/InsertViewState.hpp>
#include <IViewState.hpp>
#include <memory>
#include <vector>
#include <string>

namespace tracker::view::state
{
class ViewStateFactory
{
public:
    ViewStateFactory(int height, int width) : height(height), width(width) {}

    MenuViewStatePtr createMenuViewState() const
    {
	return std::make_shared<MenuViewState>(*this, height, width);
    }

    InsertViewStatePtr createInsertViewState() const
    {
	return std::make_shared<InsertViewState>(*this, height, width);
    }

    ExitViewStatePtr createExitViewState() const
    {
	return std::make_shared<ExitViewState>(*this);
    }
private:
    int height = 0;
    int width = 0;
};

using ViewStateFactoryPtr = std::shared_ptr<ViewStateFactory>;
}
