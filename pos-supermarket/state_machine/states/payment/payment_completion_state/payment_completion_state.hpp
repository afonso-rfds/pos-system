#pragma once

#include "invoice/invoice.hpp"
#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/pos_base_state.hpp"

class PaymentCompletionState : public BaseState
{
  public:
    PaymentCompletionState()  = default;
    ~PaymentCompletionState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
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

    /// @brief Pointer to invoice generated at payment completion
    Invoice* invoice;
};
