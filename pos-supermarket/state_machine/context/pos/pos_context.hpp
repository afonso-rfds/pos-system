#pragma once

#include "products/products.hpp"
#include "state_machine/context/context.hpp"
#include "state_machine/states/pos_state.hpp"
#include "state_machine/transaction_data/transaction_data.hpp"

#include "state_machine/states/idle_state/idle_state.hpp"
#include "state_machine/states/items_state/items_state.hpp"
#include "state_machine/states/payment/partial_payment_state/partial_payment_state.hpp"
#include "state_machine/states/payment/payment_completion_state/payment_completion_state.hpp"
#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include <string>

class POSContext : public Context
{
  public:
    POSContext(std::string storeIdentifier);
    ~POSContext() = default;

    /// @brief Process the current active state
    void processCurrentState() override;

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    void transitionToState(StateType newState) override;

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

    /// @brief Dinamically creates a new state
    /// @param newStateType State to create
    /// @return Pointer to newly created state
    POSState* createState(StateType newState);

    /// @brief Data of the transaction
    TransactionData transactionData;

    /// @brief Current active state
    std::unique_ptr<POSState> currentState;
};
