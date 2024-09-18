#include "pos_context_test.hpp"

void POSContextTest::SetUp()
{
    mockInitialState = new MockPOSState();
    mockSecondState  = new MockPOSState();

    posContext       = new POSContext("Afonso's Supermarket");
}

void POSContextTest::TearDown()
{
    delete posContext;
}

TEST_F(POSContextTest, getCurrentState)
{
    EXPECT_EQ(posContext->getCurrentState(), mockInitialState);
}

TEST_F(POSContextTest, DISABLED_transitionToState)
{
    EXPECT_CALL(*mockSecondState, enterState(::testing::Ref(*posContext))).Times(1);

    posContext->transitionToState(StateType::Idle);
    EXPECT_EQ(posContext->getCurrentState(), mockSecondState);
}

TEST_F(POSContextTest, processCurrentState)
{
    EXPECT_CALL(*mockInitialState, processState(::testing::Ref(*posContext))).Times(1);

    posContext->processCurrentState();
}