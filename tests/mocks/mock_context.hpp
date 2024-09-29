#pragma once

#include "../mocks/mock_transaction_data.hpp"
#include "state_machine/context/context.hpp"

#include <gmock/gmock.h>

class MockContext : public Context
{
  public:
    MOCK_METHOD0(processCurrentState, void());
    MOCK_METHOD1(transitionToState, void(StateType newState));
    MOCK_METHOD0(getTransactionData, TransactionData&());
};
