#pragma once

#include <IViewState.hpp>

typedef struct _win_st WINDOW;
typedef struct tagMENU MENU;
typedef struct tagITEM ITEM;

namespace tracker::view::state {
class ViewStateFactory;

class DisplayDatabaseView : public IViewState {
   public:
    DisplayDatabaseView(const ViewStateFactory &viewStateFactory);

    std::shared_ptr<IViewState> nextState(TuiView &view) override;

    ~DisplayDatabaseView();

   private:
    const ViewStateFactory &viewStateFactory;
    WINDOW *window;
    ITEM **items;
    MENU *menu;
    MENU *operationMenu;
};

using DisplayDatabaseViewPtr = std::shared_ptr<DisplayDatabaseView>;
}  // namespace tracker::view::state
