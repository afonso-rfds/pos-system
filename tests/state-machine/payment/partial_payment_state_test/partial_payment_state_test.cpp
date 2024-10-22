#include "partial_payment_state_test.hpp"

INLINE_FUNCTION void PartialPaymentStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void PartialPaymentStateTest::SetUp()
{
    partialPaymentState = new PartialPaymentState();
    posContext          = new MockContext();
    transactionData     = new TransactionData("Afonso's Supermarket");
}

void PartialPaymentStateTest::TearDown()
{
    delete partialPaymentState;
    delete posContext;
    delete transactionData;
}

TEST_F(PartialPaymentStateTest, enterState_mbway)
{
    // Redirect std::cout to a stringstream
    std::ostringstream capturedOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run state machine
    transactionData->setPaymentMethod("MBWAY");
    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    partialPaymentState->enterState(*posContext);

    // Restore std::cout to its original state
    std::cout.rdbuf(originalCoutBuffer);

    std::string expectedOutput = "MBWay: ";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

TEST_F(PartialPaymentStateTest, enterState_card)
{
    // Redirect std::cout to a stringstream
    std::ostringstream capturedOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run state machine
    transactionData->setPaymentMethod("CARD");
    EXPECT_CALL(*posContext, getTransactionData()).Times(2).WillRepeatedly(::testing::ReturnRef(*transactionData));
    partialPaymentState->enterState(*posContext);

    // Restore std::cout to its original state
    std::cout.rdbuf(originalCoutBuffer);

    std::string expectedOutput = "Card: ";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

TEST_F(PartialPaymentStateTest, enterState_cash)
{
    // Redirect std::cout to a stringstream
    std::ostringstream capturedOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run state machine
    transactionData->setPaymentMethod("CASH");
    EXPECT_CALL(*posContext, getTransactionData()).Times(2).WillRepeatedly(::testing::ReturnRef(*transactionData));
    partialPaymentState->enterState(*posContext);

    // Restore std::cout to its original state
    std::cout.rdbuf(originalCoutBuffer);

    std::string expectedOutput = "Cash: ";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}

TEST_F(PartialPaymentStateTest, processState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ partialPaymentState->processState(*posContext); }, "");
}

TEST_F(PartialPaymentStateTest, processState_overpaying_mbway)
{
    createCustomInputString("6"); // Can't pay more than remaining with MBWay

    transactionData->setRemainingToPay(5);
    transactionData->setPaymentMethod("MBWAY");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PartialPayment)).Times(1);

    partialPaymentState->processState(*posContext);
}

TEST_F(PartialPaymentStateTest, processState_overpaying_card)
{
    createCustomInputString("6"); // Can't pay more than remaining with card

    transactionData->setRemainingToPay(5);
    transactionData->setPaymentMethod("CARD");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PartialPayment)).Times(1);

    partialPaymentState->processState(*posContext);
}

TEST_F(PartialPaymentStateTest, processState_overpaying_cash)
{
    createCustomInputString("6"); // It's ok. Overpaying is allowed with cash

    transactionData->setRemainingToPay(5);
    transactionData->setPaymentMethod("CASH");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PaymentCompletion)).Times(1);

    partialPaymentState->processState(*posContext);
}

INSTANTIATE_TEST_SUITE_P(
    PartialPaymentStateInputs,
    PartialPaymentStateParamTest,
    ::testing::Values("mbway", "card", "cash"));

TEST_P(PartialPaymentStateParamTest, processState_multipleValid_CompleteTransactions)
{
    const std::string& paymentMethod = GetParam();

    createCustomInputString("5");

    transactionData->setRemainingToPay(5);
    transactionData->setPaymentMethod(paymentMethod);

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PaymentCompletion)).Times(1);

    partialPaymentState->processState(*posContext);
}

TEST_P(PartialPaymentStateParamTest, processState_multipleValid_IncompleteTransactions)
{
    const std::string& paymentMethod = GetParam();

    createCustomInputString("5");

    transactionData->setRemainingToPay(10);
    transactionData->setPaymentMethod(paymentMethod);

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PaymentSelection)).Times(1);

    partialPaymentState->processState(*posContext);
}