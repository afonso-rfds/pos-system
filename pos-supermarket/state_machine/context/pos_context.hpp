#pragma once

#include "state_machine/states/pos_state.hpp"

#include <memory>
#include <string.h>

class POSContext
{
  public:
    POSContext(POSState* initialState);
    ~POSContext() = default;

    /// @brief Process the current active state
    void processCurrentState();

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    void transitionToState(POSState* newState);

    /// @brief Get current active state instance
    /// @return Pointer to current active state
    POSState* getCurrentState();

    /// @brief Get current operator's identifier
    /// @return Current operator's identifier
    std::string getCurrentOperator();

    /// @brief Set current operator's identifier
    /// @param currentOperator operator's identifier
    void setCurrentOperator(std::string operatorIdentifier);

    /// @brief Get current transaction price
    /// @return Current transaction price
    float getCurrentTransactionPrice();

    /// @brief Get current transaction price
    /// @return Current transaction price
    void setCurrentTransactionPrice(float transactionPrice);

  private:
    /// @brief Set new state
    /// @param[in] newState New active state
    void setState(POSState* newState);

    /// @brief Current active state
    std::unique_ptr<POSState> currentState;

    /// @brief Current operator executing transactions
    std::string currentOperator;

    /// @brief Price of the current active transaction
    float currentTransactionPrice;
};
