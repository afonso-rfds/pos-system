#pragma once

#include "state_machine/pos_state.hpp"

class ErrorState : public POSState
{
  public:
    ErrorState()  = default;
    ~ErrorState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
