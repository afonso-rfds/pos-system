#include "idle_state_test.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

INLINE_FUNCTION void IdleStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

// TEST_F(IdleStateTest, enterState)
// {
//     createCustomInputString("");

//     idleState  = new IdleState();
//     posContext = new POSContext("Afonso's Supermarket");

//     // Current state is IdleState
//     ASSERT_TRUE(dynamic_cast<IdleState*>(posContext->getCurrentState()) != nullptr);
//     EXPECT_EQ(posContext->getTransactionData().getCurrentOperator(), ""); // No operator (empty string)
// }

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