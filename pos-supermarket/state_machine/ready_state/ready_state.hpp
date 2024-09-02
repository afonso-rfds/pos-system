#pragma once

#include "state_machine/pos_state.hpp"

class ReadyState : public POSState
{
  public:
    ReadyState()  = default;
    ~ReadyState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
