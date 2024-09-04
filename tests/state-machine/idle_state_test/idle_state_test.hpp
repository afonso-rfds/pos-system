#pragma once

#include "state_machine/context/pos_context.hpp"
#include "state_machine/idle_state/idle_state.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class IdleStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    POSContext* posContext;
    IdleState* idleState;
};