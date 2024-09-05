
#include "payment_selection_state_test.hpp"
#include "state_machine/states/payment_states/partial_payment_state/partial_payment_state.hpp"

INLINE_FUNCTION void PaymentSelectionStateTest::createCustomInputString(std::string inputString)
{
    std::istringstream input(inputString);
    std::cin.rdbuf(input.rdbuf());
}

TEST_F(PaymentSelectionStateTest, processState)
{
    createCustomInputString("mbway");

    paymentSelectionState = new PaymentSelectionState();
    posContext            = new POSContext(paymentSelectionState);

    paymentSelectionState->processState(*posContext);
    ASSERT_TRUE(dynamic_cast<PartialPaymentState*>(posContext->getCurrentState()) != nullptr);
}
