#include "ready_state_test.hpp"

#include "state_machine/states/idle_state/idle_state.hpp"
#include "state_machine/states/items_state/items_state.hpp"

INLINE_FUNCTION void ReadyStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void ReadyStateTest::SetUp()
{
    posContext      = new MockContext();
    readyState      = new ReadyState();
    transactionData = new TransactionData("Afonso's Supermarket");
}

void ReadyStateTest::TearDown()
{
    delete readyState;
    delete posContext;
    delete transactionData;
}

TEST_F(ReadyStateTest, enterState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ readyState->enterState(*posContext); }, "");
}

TEST_F(ReadyStateTest, processState_menu)
{
    createCustomInputString("menu");

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    readyState->enterState(*posContext);

    EXPECT_CALL(*posContext, transitionToState(StateType::Idle)).Times(1);
    readyState->processState(*posContext);
}

TEST_F(ReadyStateTest, processState_enter)
{
    createCustomInputString("");

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    readyState->enterState(*posContext);

    EXPECT_CALL(*posContext, transitionToState(StateType::Items)).Times(1);
    readyState->processState(*posContext);
}

INSTANTIATE_TEST_SUITE_P(
    ReadyStateInputs,
    ReadyStateParamTest,
    ::testing::Values("\n", "menu"));

TEST_P(ReadyStateParamTest, enterState_multipleValidInputs)
{
    const std::string& inputString = GetParam();

    createCustomInputString(inputString);

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    readyState->enterState(*posContext);
}