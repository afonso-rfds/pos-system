#pragma once

#include "state_machine/pos_context.hpp"
#include "state_machine/ready_state/ready_state.hpp"

#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class ReadyStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    POSContext* posContext;
    ReadyState* readyState;
};