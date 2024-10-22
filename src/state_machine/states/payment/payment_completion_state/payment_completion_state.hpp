#pragma once

#include "database/databases_manager/databases_manager.hpp"
#include "invoice/invoice.hpp"
#include "state_machine/context/pos/pos_context.hpp"
#include "state_machine/states/pos_base_state.hpp"

class PaymentCompletionState : public BaseState
{
  public:
    PaymentCompletionState()  = default;
    ~PaymentCompletionState() = default;

    void enterState(Context& context) override;
    void processState(Context& context) override;

  private:
    /// @brief Save current transaction in a database
    void saveTransaction();

    /// @brief Generates an invoice number
    /// @return 10 digits invoice number
    std::string generateInvoiceNumber();

    /// @brief Prompt possible commands after finalizing the transaction
    void promptSaveStartExit();

    /// @brief Process the end of the transaction after saving
    /// @param context Current state machine context
    void processEndOfTransaction(Context& context);

    /// @brief Creates an invoice
    /// @param context Current state machine context
    /// @return pointer to invoice created
    Invoice* createInvoice(Context& context);

    /// @brief Pointer to invoice generated at payment completion
    Invoice* invoice;

    /// @brief Member that deals with the databases
    DatabasesManager databasesManager;
};
