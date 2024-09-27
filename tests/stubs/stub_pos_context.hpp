#pragma once

#include "../mocks/mock_transaction_data.hpp"
#include "state_machine/context/context.hpp"

class StubPOSContext : public Context
{
  public:
    StubPOSContext() = default;

    void processCurrentState() override{};
    void transitionToState(StateType newState) override{};
    TransactionData& getTransactionData() override { return mockTransactionData; }

  private:
    MockTransactionData mockTransactionData;
};