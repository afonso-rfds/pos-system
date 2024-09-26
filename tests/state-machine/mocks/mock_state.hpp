#pragma once

#include "state_machine/states/pos_state.hpp"

#include <gmock/gmock.h>

class MockPOSState : public POSState
{
  public:
    MOCK_METHOD1(processState, void(Context& context));
    MOCK_METHOD1(enterState, void(Context& context));
};
