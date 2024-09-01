#pragma once

#include "state_machine/pos_context.hpp"

#include "mock_state.hpp"
#include <gmock/gmock.h> // Ensure this is included
#include <gtest/gtest.h>

class POSContextTest : public ::testing::Test
{
  protected:
    POSContext* posContext;
    MockPOSState* mockInitialState;
    MockPOSState* mockSecondState;

    void SetUp() override;
    void TearDown() override;
};
