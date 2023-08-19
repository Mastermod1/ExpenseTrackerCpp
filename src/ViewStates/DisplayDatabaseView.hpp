#pragma once

#include <IViewState.hpp>
#include <vector>
#include <ViewStates/Types/Field.hpp>

typedef struct _win_st WINDOW;
typedef struct tagMENU MENU;
typedef struct tagITEM ITEM;

namespace tracker::helpers
{
struct Size;
}  // namespace tracker::helpers

namespace tracker::view::state
{
class ViewStateFactory;

class DisplayDatabaseView : public IViewState
{
public:
    DisplayDatabaseView(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState(TuiView& view) override;

    ~DisplayDatabaseView();
private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    WINDOW* window;
    ITEM** items;
    MENU* menu;
    MENU* operationMenu;
    std::shared_ptr<helpers::Size> winSize;
    std::shared_ptr<helpers::Size> scrSize;
};

using DisplayDatabaseViewPtr = std::shared_ptr<DisplayDatabaseView>;
}
