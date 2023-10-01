#pragma once

#include <IViewState.hpp>
#include <memory>

typedef struct _win_st WINDOW;
typedef struct tagMENU MENU;
typedef struct tagITEM ITEM;

namespace tracker::view::state {
class ViewStateFactory;

class MenuViewState : public IViewState {
   public:
    MenuViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState(TuiView& view) override;

    ~MenuViewState();

   private:
    const ViewStateFactory& viewStateFactory;
    WINDOW* window;
    ITEM** items;
    MENU* menu;
};

using MenuViewStatePtr = std::shared_ptr<MenuViewState>;
}  // namespace tracker::view::state
