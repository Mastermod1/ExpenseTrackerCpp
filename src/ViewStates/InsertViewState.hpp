#pragma once

#include <IViewState.hpp>
#include <vector>
#include <ViewStates/Types/Field.hpp>

namespace tracker::view::state
{
class ViewStateFactory;

class InsertViewState : public IViewState
{
public:
    InsertViewState(const ViewStateFactory& viewStateFactory, int height, int width) ;

    void draw() override;
    std::shared_ptr<IViewState> nextState() override;
private:
    int clampedHighlightPos();
    void readLine();
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<types::Field> fields{{"--INSERT ROW--"}, {"", true}, {"Back"}};
    int fieldCount = fields.size();
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}
