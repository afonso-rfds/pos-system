#include "items_state_test.hpp"

#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

INLINE_FUNCTION void ItemsStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString + "\n");
    std::cin.rdbuf(input.rdbuf());
    std::cin.clear();
}

void ItemsStateTest::SetUp()
{
    posContext      = new MockContext();
    itemsState      = new ItemsState();
    transactionData = new TransactionData("Afonso's Supermarket");
}

void ItemsStateTest::TearDown()
{
    delete posContext;
    delete itemsState;
    delete transactionData;
}

TEST_F(ItemsStateTest, enterState)
{
    itemsState->enterState(*posContext);
}

TEST_F(ItemsStateTest, processState_invalidInput)
{
    createCustomInputString("invalidInput");

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_DEATH({ itemsState->processState(*posContext); }, "");
}

TEST_F(ItemsStateTest, processState_cancel)
{
    createCustomInputString("cancel");

    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);
    itemsState->processState(*posContext);
}

TEST_F(ItemsStateTest, processState_invalid_done)
{
    createCustomInputString("done");

    EXPECT_CALL(*posContext, getTransactionData()).Times(1).WillOnce(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::Items)).Times(1);

    itemsState->processState(*posContext);
}

TEST_F(ItemsStateTest, processState_validEAN13)
{
    // 2 valid EAN13s followed by the 'done' instruction (valid done)
    std::istringstream input("0000000000000\n0000000000001\ndone");
    std::cin.rdbuf(input.rdbuf());

    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::PaymentSelection)).Times(1);

    itemsState->processState(*posContext);
}

TEST_F(ItemsStateTest, processState_invalidEAN13)
{
    // Invalid EAN13 (12 characters instead of 13)
    std::istringstream input("000000000000\ncancel");
    std::cin.rdbuf(input.rdbuf());

    // Redirect std::cout to a stringstream
    std::ostringstream capturedOutput;
    std::streambuf* originalCoutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(capturedOutput.rdbuf());

    // Run state machine
    EXPECT_CALL(*posContext, getTransactionData()).WillRepeatedly(::testing::ReturnRef(*transactionData));
    EXPECT_CALL(*posContext, transitionToState(StateType::Ready)).Times(1);
    itemsState->processState(*posContext);

    // Restore std::cout to its original state
    std::cout.rdbuf(originalCoutBuffer);

    std::string expectedOutput = "[Done/Cancel/EAN13]: \nInvalid EAN13. Try again.\n\n[Done/Cancel/EAN13]: ";
    EXPECT_EQ(capturedOutput.str(), expectedOutput);
}
