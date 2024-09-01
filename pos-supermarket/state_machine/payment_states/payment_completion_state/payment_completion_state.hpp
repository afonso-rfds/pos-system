#pragma once

#include "state_machine/pos_state.hpp"

class PaymentCompletionState : public POSState
{
  public:
    PaymentCompletionState()  = default;
    ~PaymentCompletionState() = default;

    void handleInput(POSContext& context, const std::string& input) override;
    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
};
