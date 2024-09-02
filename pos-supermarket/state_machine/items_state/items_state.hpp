#pragma once

#include "state_machine/pos_state.hpp"

class ItemsState : public POSState
{
  public:
    ItemsState()  = default;
    ~ItemsState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;
};
