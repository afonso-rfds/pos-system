#pragma once

#include <string>

enum class StateType
{
    Idle,
    Ready,
    Items,
    PaymentSelection,
    PartialPayment,
    PaymentCompletion
};

class Context
{
  public:
    /// @brief Process the current active state
    virtual void processCurrentState() = 0;

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    virtual void transitionToState(StateType newState) = 0;

    /// @brief Access the transaction data
    /// @return Reference to TransactionData
    // TransactionData& getTransactionData();
};