
#include "payment_selection_state_test.hpp"

INLINE_FUNCTION void PaymentSelectionTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void PaymentSelectionTest::SetUp()
{
    posContext            = new MockContext();
    paymentSelectionState = new PaymentSelectionState();
    transactionData       = new TransactionData("Afonso's Supermarket");
}

void PaymentSelectionTest::TearDown()
{
    delete paymentSelectionState;
    delete posContext;
    delete transactionData;
}

TEST_F(PaymentSelectionTest, enterState)
{
    EXPECT_CALL(*posContext, getTransactionData()).Times(3).WillRepeatedly(::testing::ReturnRef(*transactionData));

    paymentSelectionState->enterState(*posContext);
}

TEST_F(PaymentSelectionTest, processState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ paymentSelectionState->processState(*posContext); }, "");
}

INSTANTIATE_TEST_SUITE_P(
    PaymentSelectionInputs,
    PaymentSelectionParamTest,
    ::testing::Values("mbway", "card", "cash"));

TEST_P(PaymentSelectionParamTest, processState_multipleValidInputs)
{
    const std::string& inputString = GetParam();

    createCustomInputString(inputString);

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PartialPayment)).Times(1);

    paymentSelectionState->processState(*posContext);
}