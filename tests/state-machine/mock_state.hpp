// mock_pos_state.hpp
#pragma once

#include "state_machine/pos_state.hpp"

#include <gmock/gmock.h>

class MockPOSState : public POSState
{
  public:
    MOCK_METHOD2(handleInput, void(POSContext& context, const std::string& input));
    MOCK_METHOD1(enterState, void(POSContext& context));
    MOCK_METHOD1(exitState, void(POSContext& context));
};
