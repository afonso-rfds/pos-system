#pragma once

#include "state_machine/context/pos/pos_context.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"

#include <gtest/gtest.h>
#include <stdexcept>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class IdleStateTest : public ::testing::Test
{
  protected:
    /// @brief Create a personalized input string and redirect std::cin
    /// @param inputString string to mock as user's input
    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    // void SetUp() override;
    // void TearDown() override;

    Context* posContext;
    IdleState* idleState;
};

class ExitException : public std::exception
{
    const char* what() const noexcept override
    {
        return "Program exited successfully";
    }
};
