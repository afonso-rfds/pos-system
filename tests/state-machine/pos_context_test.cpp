#include "pos_context_test.hpp"

void POSContextTest::SetUp()
{
    mockInitialState = new MockPOSState();
    mockSecondState  = new MockPOSState();

    posContext       = new POSContext(mockInitialState);
}

void POSContextTest::TearDown()
{
    delete posContext;
}

TEST_F(POSContextTest, getCurrentState)
{
    EXPECT_EQ(posContext->getCurrentState(), mockInitialState);
}

TEST_F(POSContextTest, transitionToState)
{
    EXPECT_CALL(*mockInitialState, exitState(::testing::Ref(*posContext))).Times(1);
    EXPECT_CALL(*mockSecondState, enterState(::testing::Ref(*posContext))).Times(1);

    posContext->transitionToState(mockSecondState);
    EXPECT_EQ(posContext->getCurrentState(), mockSecondState);
}

TEST_F(POSContextTest, handleInput)
{
    EXPECT_CALL(*mockInitialState, handleInput(::testing::Ref(*posContext), ::testing::_)).Times(1);

    posContext->handleInput("Test Input");
}