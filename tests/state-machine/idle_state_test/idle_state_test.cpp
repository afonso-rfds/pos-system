#include "idle_state_test.hpp"

INLINE_FUNCTION void IdleStateTest::createCustomInputString(std::string inputString)
{
    // Create a personalized input string and redirect std::cin
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

void IdleStateTest::SetUp()
{

    createCustomInputString("");

    idleState      = new IdleState();

    mockReadyState = new MockPOSState();
    mockContext    = new MockPOSContext(idleState);

    // Restore cin's buffer
    // std::cin.rdbuf(nullptr);
}

void IdleStateTest::TearDown()
{
}

TEST_F(IdleStateTest, enterState)
{
    EXPECT_TRUE(true);
}

TEST_F(IdleStateTest, processState)
{
    EXPECT_CALL(*mockReadyState, enterState(::testing::Ref(*mockContext))).Times(1);
    EXPECT_CALL(*mockContext, transitionToState(::testing::Ref(*mockReadyState))).Times(1);

    createCustomInputString("User");

    idleState->processState(*mockContext);
}