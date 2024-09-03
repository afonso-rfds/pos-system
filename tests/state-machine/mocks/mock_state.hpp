#pragma once

#include "state_machine/pos_state.hpp"

#include <gmock/gmock.h>

class MockPOSState : public POSState
{
  public:
    MOCK_METHOD1(processState, void(POSContext& context));
    MOCK_METHOD1(enterState, void(POSContext& context));
    MOCK_METHOD1(exitState, void(POSContext& context));
};
