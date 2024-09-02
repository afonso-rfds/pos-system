#pragma once

#include "state_machine/pos_state.hpp"

class PartialPaymentState : public POSState
{
  public:
    PartialPaymentState()  = default;
    ~PartialPaymentState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
