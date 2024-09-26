#pragma once

#include "state_machine/context/pos/pos_context.hpp"
#include "state_machine/states/pos_base_state.hpp"

class ReadyState : public BaseState
{
  public:
    ReadyState()  = default;
    ~ReadyState() = default;

    void enterState(POSContext& context) override;
    void processState(POSContext& context) override;
};
