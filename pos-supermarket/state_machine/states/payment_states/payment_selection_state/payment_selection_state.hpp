#pragma once

#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

class PaymentSelectionState : public POSState
{
  public:
    PaymentSelectionState()  = default;
    ~PaymentSelectionState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Gets input from the user
    void getUserInput();

    /// @brief Commands from the user
    std::string userInput;
};
