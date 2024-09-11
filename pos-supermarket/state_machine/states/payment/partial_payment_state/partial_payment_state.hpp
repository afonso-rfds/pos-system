#pragma once

#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/pos_base_state.hpp"

class PartialPaymentState : public BaseState
{
  public:
    PartialPaymentState()  = default;
    ~PartialPaymentState() = default;

    void enterState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Check weather the operator's number is valid (number until 2 decimals only)
    /// @param number Number to validade
    /// @return true:  Valid number.
    ///         false: Invalid number
    bool isValidNumber(std::string number);

    /// @brief Handles invalid user input
    /// @param context Current state machine context
    void handleInvalidInput(POSContext& context);

    /// @brief Check if user is overpaying
    /// @param payment Payment made
    /// @param context Current state machine context
    /// @return true: user is overpaying. false: user is NOT overpaying
    bool isOverpaying(float payment, const POSContext& context);

    /// @brief Update remaining value to pay
    /// @param payment Payment made
    /// @param context Current state machine context
    void updateRemainingToPay(float payment, POSContext& context);

    /// @brief Checks if payment is complete
    /// @param context Current state machine context
    /// @return true: payment complete. false: payment incomplete
    bool isPaymentComplete(const POSContext& context);

    /// @brief Validate that there is no overpayment with MBWay or Card
    /// @param payment Payment made
    /// @param context Current state machine context
    /// @return true: Valid payment. False: Invalid payment
    bool isValidPayment(float payment, POSContext& context);
};
