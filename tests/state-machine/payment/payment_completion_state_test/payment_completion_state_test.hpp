#pragma once

#include "../../../mocks/mock_context.hpp"
#include "state_machine/states/payment/payment_completion_state/payment_completion_state.hpp"
#include "state_machine/transaction_data/transaction_data.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class PaymentCompletionStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    void SetUp() override;
    void TearDown() override;

    PaymentCompletionState* paymentCompletionState;
    TransactionData* transactionData;

    MockContext* posContext;
};
