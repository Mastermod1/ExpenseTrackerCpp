#pragma once

#include <IViewState.hpp>

typedef struct _win_st WINDOW;
typedef struct formnode FORM;
typedef struct fieldnode FIELD;

namespace tracker::view::state {
class ViewStateFactory;

class InsertViewState : public IViewState {
   public:
    InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState(TuiView& view) override;

    ~InsertViewState();

   private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    WINDOW* window;
    FORM* form;
    FIELD** formFields;
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}  // namespace tracker::view::state
