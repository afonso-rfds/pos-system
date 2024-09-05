#include "payment_selection_state.hpp"
#include "config.hpp"
#include "state_machine/states/payment_states/partial_payment_state/partial_payment_state.hpp"

#include "iostream"
#include <algorithm>
#include <limits.h>

void PaymentSelectionState::enterState(POSContext& context)
{
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "  --- Total to pay:     " << context.getSubtotalPrice() + context.getTaxPrice() << "€ ---" << std::endl;
    std::cout << "  --- Remaining to pay: " << context.getRemainingToPay() << "€ ---" << std::endl;
    std::cout << "-----------------------------------" << std::endl
              << std::endl;
    ;
    do
    {
        std::cout << "You can pay via MBWay, card or cash" << std::endl;
        std::cout << "Payment method: ";

        getUserInput();

    } while (userInput != "MBWAY" && userInput != "CARD" && userInput != "CASH");

    context.setPaymentMethod(userInput);
}

void PaymentSelectionState::exitState(POSContext& context)
{
}

void PaymentSelectionState::processState(POSContext& context)
{
    context.transitionToState(new PartialPaymentState);
}

void PaymentSelectionState::getUserInput()
{
    //  In debug mode don't flush cin buffer
#ifndef DEBUG_MODE_ENABLED
    std::cin.ignore(INT_MAX, '\n');
#endif
    std::getline(std::cin, userInput);
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    std::cout << std::endl
              << std::endl;
}