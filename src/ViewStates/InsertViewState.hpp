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

class InsertViewState : public IViewState
{
public:
    InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width);

    std::shared_ptr<IViewState> nextState() override;

    ~InsertViewState();
private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<types::Field> fields{{"--INSERT ROW--"}, {"XD", true}, {"XD", true}, {"XD", true}, {"Back"}};
    int fieldCount = fields.size();
    WINDOW* window;
    ITEM** items;
    MENU* menu;
    std::shared_ptr<helpers::Size> winSize;
    std::shared_ptr<helpers::Size> scrSize;
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}
