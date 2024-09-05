#pragma once

#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

class PaymentCompletionState : public POSState
{
  public:
    PaymentCompletionState()  = default;
    ~PaymentCompletionState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Gets input from the user
    void getUserInput();

    /// @brief Print invoice in the screen
    /// @param context Current state machine context
    void printInvoice(POSContext& context);

    /// @brief Print the registered items
    /// @param context Current state machine context
    void printRegisteredItems(POSContext& context) const;

    /// @brief Print data such as total, change, operator, invoice number, etc
    /// @param context Current state machine context
    void printData(POSContext& context) const;

    /// @brief Save current transaction in a database
    /// @param context Current state machine context
    void saveTransaction(POSContext& context);

    /// @brief Generates an invoice number
    /// @return 10 digits invoice number
    std::string generateInvoiceNumber();

    /// @brief Commands from the user
    std::string userInput;
};
