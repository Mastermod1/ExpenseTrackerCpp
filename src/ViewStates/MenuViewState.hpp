#pragma once

#include <IViewState.hpp>
#include <vector>
#include <ViewStates/Types/Field.hpp>

typedef struct tagMENU MENU;
typedef struct _win_st WINDOW;
typedef struct tagITEM ITEM;

namespace tracker::helpers
{
struct Size;
}  // namespace tracker::helpers

namespace tracker::view::state
{
class ViewStateFactory;

class MenuViewState : public IViewState
{
public:
    MenuViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState() override;

    ~MenuViewState();
private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<types::Field> fields{{"--MENU--"}, {"Insert row"}, {"Display database"}, {"Exit"}};
    int fieldCount = fields.size();
    WINDOW* window;
    ITEM** items;
    MENU* menu;
    std::shared_ptr<helpers::Size> winSize;
    std::shared_ptr<helpers::Size> scrSize;
};

using MenuViewStatePtr = std::shared_ptr<MenuViewState>;
}
