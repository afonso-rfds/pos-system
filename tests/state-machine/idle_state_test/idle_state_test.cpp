#include "idle_state_test.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

INLINE_FUNCTION void IdleStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

TEST_F(IdleStateTest, enterState)
{
    EXPECT_TRUE(true);
}

TEST_F(IdleStateTest, processState)
{
    createCustomInputString("");

    idleState  = new IdleState();
    posContext = new POSContext(idleState);

    ASSERT_TRUE(dynamic_cast<IdleState*>(posContext->getCurrentState()) != nullptr);

    createCustomInputString("User");
    idleState->processState(*posContext);
    ASSERT_TRUE(dynamic_cast<ReadyState*>(posContext->getCurrentState()) != nullptr);
}