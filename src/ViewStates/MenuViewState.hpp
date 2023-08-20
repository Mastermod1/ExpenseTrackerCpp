#pragma once

#include <IViewState.hpp>
#include <ViewStates/Types/Field.hpp>
#include <vector>

typedef struct _win_st WINDOW;
typedef struct tagMENU MENU;
typedef struct tagITEM ITEM;

namespace tracker::helpers {
struct Size;
}  // namespace tracker::helpers

namespace tracker::view::state {
class ViewStateFactory;

class MenuViewState : public IViewState {
   public:
    MenuViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState(TuiView& view) override;

    ~MenuViewState();

   private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    WINDOW* window;
    ITEM** items;
    MENU* menu;
    std::shared_ptr<helpers::Size> winSize;
    std::shared_ptr<helpers::Size> scrSize;
};

using MenuViewStatePtr = std::shared_ptr<MenuViewState>;
}  // namespace tracker::view::state
