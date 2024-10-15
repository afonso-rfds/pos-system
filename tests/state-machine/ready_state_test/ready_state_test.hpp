#pragma once

#include "../../mocks/mock_context.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"
#include "state_machine/transaction_data/transaction_data.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class ReadyStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    void SetUp() override;
    void TearDown() override;

    ReadyState* readyState;
    TransactionData* transactionData;

    MockContext* posContext;
};

// Parameterized test case for inputs "enter", "menu"
class ReadyStateParamTest : public ReadyStateTest, public ::testing::WithParamInterface<std::string>
{
};