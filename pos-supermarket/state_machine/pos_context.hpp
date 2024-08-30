#pragma once

#include <memory>
#include "pos_state.hpp"

class POSContext 
{
private:
    std::unique_ptr<POSState> currentState;

public:
    POSContext(POSState* initialState);
    ~POSContext() = default;

    void setState(POSState* newState);
    void handleInput(const std::string& input);
    void transitionToState(POSState* newState);
};
