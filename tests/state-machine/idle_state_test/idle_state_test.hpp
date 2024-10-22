#pragma once

#include "../../mocks/mock_context.hpp"
#include "../../mocks/mock_databases_manager.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"
#include "state_machine/transaction_data/transaction_data.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class IdleStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    void SetUp() override;
    void TearDown() override;

    IdleState* idleState;
    TransactionData* transactionData;

    MockContext* posContext;
};

// Parameterized test case for inputs "\n", "show", and "clean"
class IdleStateParamTest : public IdleStateTest, public ::testing::WithParamInterface<std::string>
{
};
