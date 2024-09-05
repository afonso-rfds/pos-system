#pragma once

#include "invoice/invoice.hpp"
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

    /// @brief Save current transaction in a database
    /// @param context Current state machine context
    void saveTransaction(POSContext& context);

    /// @brief Generates an invoice number
    /// @return 10 digits invoice number
    std::string generateInvoiceNumber();

    /// @brief Creates an invoice
    /// @param context Current state machine context
    /// @return pointer to invoice created
    Invoice* createInvoice(POSContext& context);

    /// @brief Commands from the user
    std::string userInput;

    Invoice* invoice;
};
