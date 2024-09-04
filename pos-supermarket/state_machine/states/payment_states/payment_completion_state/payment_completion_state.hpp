#pragma once

#include "state_machine/states/pos_state.hpp"

class PaymentCompletionState : public POSState
{
  public:
    PaymentCompletionState()  = default;
    ~PaymentCompletionState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
