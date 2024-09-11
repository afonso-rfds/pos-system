#pragma once

#include "products/products.hpp"
#include "state_machine/states/pos_state.hpp"
#include "state_machine/transaction_data/transaction_data.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class POSContext
{
  public:
    POSContext(POSState* initialState, std::string storeIdentifier);
    ~POSContext() = default;

    /// @brief Process the current active state
    void processCurrentState();

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    void transitionToState(POSState* newState);

    //**** -------------- Getters -------------- ****

    /// @brief Get current active state instance
    /// @return Pointer to current active state
    POSState* getCurrentState() const;

    /// @brief Access the transaction data
    /// @return Reference to TransactionData
    TransactionData& getTransactionData();

  private:
    /// @brief Set new state
    /// @param[in] newState New active state
    void setState(POSState* newState);

    /// @brief Data of the transaction
    TransactionData transactionData;

    /// @brief Current active state
    std::unique_ptr<POSState> currentState;
};
