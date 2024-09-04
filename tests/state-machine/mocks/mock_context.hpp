#pragma once

#include "state_machine/context/pos_context.hpp"

#include <gmock/gmock.h>

class MockPOSContext : public POSContext
{
  public:
    MockPOSContext(POSState* initialState) : POSContext(initialState) {}

    MOCK_METHOD0(processCurrentState, void(void));
    MOCK_METHOD1(transitionToState, void(POSState& newState));
    MOCK_METHOD0(getCurrentState, POSState*(void));
};