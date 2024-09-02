#pragma once

#include "state_machine/pos_state.hpp"

class PaymentSelectionState : public POSState
{
  public:
    PaymentSelectionState()  = default;
    ~PaymentSelectionState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
