#include "idle_state_test.hpp"

#include "../../stubs/stub_pos_context.hpp"

INLINE_FUNCTION void IdleStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

TEST_F(IdleStateTest, enterState_exit)
{
    createCustomInputString("exit");

    idleState  = new IdleState();
    posContext = new StubPOSContext();

    ASSERT_EXIT({ idleState->enterState(*posContext); }, ::testing::ExitedWithCode(0), "");
}

// TEST_F(IdleStateTest, processState)
// {
//     createCustomInputString("");

//     idleState  = new IdleState();
//     posContext = new POSContext("Afonso's Supermarket");

//     createCustomInputString("User");
//     idleState->processState(*posContext);

//     // Current state is ReadyState. Current operator's identifier is 'User'
//     ASSERT_TRUE(dynamic_cast<ReadyState*>(posContext->getCurrentState()) != nullptr);
//     EXPECT_EQ(posContext->getTransactionData().getCurrentOperator(), "USER");
// }