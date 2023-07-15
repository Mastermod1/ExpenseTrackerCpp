#pragma once

#include <IViewState.hpp>
#include <vector>
#include <string>

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
    const ViewStateFactory& viewStateFactory;
    int height;
    int width;
    std::vector<std::string> menuFields{"--INSERT ROW--", "Dummy", "Back"};
    int fieldCount = menuFields.size();
    State state = State::Insert;
};

using InsertViewStatePtr = std::shared_ptr<InsertViewState>;
}
