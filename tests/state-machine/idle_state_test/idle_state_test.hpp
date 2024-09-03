#pragma once

#include "../mocks/mock_context.hpp"
#include "../mocks/mock_state.hpp"
#include "state_machine/idle_state/idle_state.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define INLINE_FUNCTION inline __attribute__((always_inline))

class IdleStateTest : public ::testing::Test
{
  protected:
    MockPOSContext* mockContext;
    MockPOSState* mockReadyState;

    IdleState* idleState;

    INLINE_FUNCTION void createCustomInputString(std::string inputString);

    void SetUp() override;
    void TearDown() override;
};