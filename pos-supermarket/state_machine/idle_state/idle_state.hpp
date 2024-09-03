#pragma once

#include <string.h>

#include "iostream"
#include "state_machine/pos_context.hpp"
#include "state_machine/pos_state.hpp"
#include "state_machine/ready_state/ready_state.hpp"

class IdleState : public POSState
{
  public:
    IdleState()  = default;
    ~IdleState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Print "welcome" screen and process commands
    void showWelcomeScreen();

    /// @brief Check weather the operator's name is valid (alphabetic chars only)
    /// @param operatorsName Name of operator to validade
    /// @return true:  Valid name.
    ///         false: Invalid name
    bool isValidName(std::string operatorsName);

    /// @brief Commands from the user
    std::string userInput;
};
