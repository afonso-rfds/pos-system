#include "payment_completion_state_test.hpp"

INLINE_FUNCTION void PaymentCompletionStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void PaymentCompletionStateTest::SetUp()
{
    paymentCompletionState = new PaymentCompletionState();
    posContext             = new MockContext();
    transactionData        = new TransactionData("Afonso's Supermarket");
}

void PaymentCompletionStateTest::TearDown()
{
    delete paymentCompletionState;
    delete posContext;
    delete transactionData;
}

TEST_F(PaymentCompletionStateTest, enterState)
{
    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));

    paymentCompletionState->enterState(*posContext);
}

TEST_F(PaymentCompletionStateTest, processState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ paymentCompletionState->processState(*posContext); }, "");
}

TEST_F(PaymentCompletionStateTest, processState_startNewTransaction)
{
    createCustomInputString("start");

    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);
    paymentCompletionState->processState(*posContext);
}

TEST_F(PaymentCompletionStateTest, processState_exit)
{
    createCustomInputString("exit");

    ASSERT_EXIT({ paymentCompletionState->processState(*posContext); }, ::testing::ExitedWithCode(0), "");
}

TEST_F(PaymentCompletionStateTest, processState_saveTransaction_start)
{
    std::istringstream input("save\nstart"); // 'save' followed by a 'start'
    std::cin.rdbuf(input.rdbuf());

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);

    paymentCompletionState->enterState(*posContext);
    paymentCompletionState->processState(*posContext);
}

TEST_F(PaymentCompletionStateTest, DISABLED_processState_saveTransaction_invalidInput)
{
    std::istringstream input("save\ninvalidInput"); // 'save' followed by an invalid input
    std::cin.rdbuf(input.rdbuf());

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);

    paymentCompletionState->enterState(*posContext);
    EXPECT_DEATH({ paymentCompletionState->processState(*posContext); }, "");
}

TEST_F(PaymentCompletionStateTest, DISABLED_processState_saveTransaction_exit)
{
    std::istringstream input("save\nexit"); // 'save' followed by an 'exit'
    std::cin.rdbuf(input.rdbuf());

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));

    paymentCompletionState->enterState(*posContext);
    ASSERT_EXIT({ paymentCompletionState->processState(*posContext); }, ::testing::ExitedWithCode(0), "");
}
