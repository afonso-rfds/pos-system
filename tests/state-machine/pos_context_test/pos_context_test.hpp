#pragma once

#include "../mocks/mock_state.hpp"
#include "state_machine/pos_context.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

class POSContextTest : public ::testing::Test
{
  protected:
    void SetUp() override;
    void TearDown() override;

    MockPOSState* mockInitialState;
    MockPOSState* mockSecondState;

    POSContext* posContext;
};
