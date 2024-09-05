#pragma once

#include <string.h>

#include "iostream"
#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

class IdleState : public POSState
{
  public:
    IdleState()  = default;
    ~IdleState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Gets input from the user
    void getUserInput();

    /// @brief Check weather the operator's name is valid (alphabetic chars only)
    /// @param operatorsName Name of operator to validade
    /// @return true:  Valid name.
    ///         false: Invalid name
    bool isValidName(std::string operatorsName);

    /// @brief Process the beginning of a transaction
    /// @param context Current state machine context
    void processTransaction(POSContext& context);

    /// @brief Commands from the user
    std::string userInput;
};
