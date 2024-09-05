#include "items_state_test.hpp"

#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

INLINE_FUNCTION void ItemsStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

TEST_F(ItemsStateTest, enterState)
{
    EXPECT_TRUE(true);
}

TEST_F(ItemsStateTest, processState_toReadyState)
{
    createCustomInputString("cancel");

    itemsState = new ItemsState();
    posContext = new POSContext(itemsState);

    itemsState->processState(*posContext);
    ASSERT_TRUE(dynamic_cast<ReadyState*>(posContext->getCurrentState()) != nullptr);
}

TEST_F(ItemsStateTest, processState_toPaymentSelectionState)
{
    createCustomInputString("");

    itemsState = new ItemsState();
    posContext = new POSContext(itemsState);

    createCustomInputString("done");

    itemsState->processState(*posContext);
    EXPECT_EQ(posContext->getSubtotalPrice(), 0);
}
