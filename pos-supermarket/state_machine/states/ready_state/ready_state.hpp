#pragma once

#include "state_machine/context/pos/pos_context.hpp"
#include "state_machine/states/pos_base_state.hpp"

class ReadyState : public BaseState
{
  public:
    ReadyState()  = default;
    ~ReadyState() = default;

    void enterState(Context& context) override;
    void processState(Context& context) override;
};
