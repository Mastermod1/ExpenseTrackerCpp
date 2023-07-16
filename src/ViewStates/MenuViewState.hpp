#pragma once

#include <IViewState.hpp>
#include <vector>
#include <ViewStates/Types/Field.hpp>

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
    std::vector<types::Field> fields{{"--MENU--"}, {"Insert row"}, {"Display database"}, {"Exit"}};
    int fieldCount = fields.size();
};

using MenuViewStatePtr = std::shared_ptr<MenuViewState>;
}
