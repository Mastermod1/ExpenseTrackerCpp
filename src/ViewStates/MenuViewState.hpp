#pragma once

#include <IViewState.hpp>
#include <vector>
#include <string>

namespace tracker::view::state
{
class ViewStateFactory;

class MenuViewState : public IViewState
{
public:
    MenuViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    void draw() override;
    std::shared_ptr<IViewState> nextState() override;

private:
    int clampedHighlightPos();

    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<std::string> menuFields{"--MENU--", "Insert row", "Display database", "Exit"};
    int fieldCount = menuFields.size();
};

using MenuViewStatePtr = std::shared_ptr<MenuViewState>;
}
