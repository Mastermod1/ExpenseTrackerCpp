#pragma once

#include <IViewState.hpp>
#include <vector>
#include <ViewStates/Types/Field.hpp>

typedef struct _win_st WINDOW;
typedef struct formnode FORM;
typedef struct fieldnode FIELD;

namespace tracker::helpers
{
struct Size;
}  // namespace tracker::helpers

namespace tracker::view::state
{
class ViewStateFactory;

class InsertViewState : public IViewState
{
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
    std::shared_ptr<helpers::Size> winSize;
    std::shared_ptr<helpers::Size> scrSize;
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}
