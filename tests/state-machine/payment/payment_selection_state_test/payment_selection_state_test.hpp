#pragma once

#include "state_machine/context/pos/pos_context.hpp"
#include "state_machine/states/items_state/items_state.hpp"
#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class PaymentSelectionStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    POSContext* posContext;
    PaymentSelectionState* paymentSelectionState;
};