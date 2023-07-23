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

    std::shared_ptr<IViewState> nextState() override;
private:
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<types::Field> fields{{"--INSERT ROW--"}, {"XD", true}, {"XD", true}, {"XD", true}, {"Back"}};
    int fieldCount = fields.size();
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}
