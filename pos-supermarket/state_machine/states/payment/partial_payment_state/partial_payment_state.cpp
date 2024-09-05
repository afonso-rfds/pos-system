#include "partial_payment_state.hpp"
#include "config.hpp"
#include "state_machine/states/payment/payment_completion_state/payment_completion_state.hpp"
#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"

#include "iostream"
#include <algorithm>
#include <limits.h>
#include <regex>

void PartialPaymentState::enterState(POSContext& context)
{
    if (context.getPaymentMethod() == "MBWAY")
    {
        std::cout << "MBWay: ";
    }
    else if (context.getPaymentMethod() == "CARD")
    {
        std::cout << "Card: ";
    }
    else
    {
        std::cout << "Cash: ";
    }
}

void PartialPaymentState::exitState(POSContext& context)
{
}

void PartialPaymentState::processState(POSContext& context)
{
    getUserInput();
    while (!isValidNumber(userInput))
    {
        handleInvalidInput(context);
    }

    float payment = std::stof(userInput);

    if (!isValidPayment(payment, context))
    {
        return;
    }

    updateRemainingToPay(payment, context);

    if (isPaymentComplete(context))
    {
        context.transitionToState(new PaymentCompletionState);
    }
    else
    {
        context.transitionToState(new PaymentSelectionState);
    }
}

void PartialPaymentState::getUserInput()
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

bool PartialPaymentState::isValidNumber(std::string number)
{
    // Regex to match a number with optional decimals (up to 2 decimal places)
    std::regex numberRegex("^\\d+(\\.\\d{1,2})?$");

    // Return true if the input matches the regex, false otherwise
    return std::regex_match(number, numberRegex);
}

void PartialPaymentState::handleInvalidInput(POSContext& context)
{
    std::cout << std::endl
              << std::endl
              << "Invalid Number. Please try again." << std::endl;
    enterState(context);
    getUserInput();
}

bool PartialPaymentState::isOverpaying(float payment, const POSContext& context)
{
    return payment > context.getRemainingToPay();
}

void PartialPaymentState::updateRemainingToPay(float payment, POSContext& context)
{
    if (isOverpaying(payment, context))
    {
        context.setCashChange(payment - context.getRemainingToPay());
        context.setRemainingToPay(0);
    }
    else
    {
        context.setRemainingToPay(context.getRemainingToPay() - payment);
    }
}

bool PartialPaymentState::isPaymentComplete(const POSContext& context)
{
    return (context.getRemainingToPay() == 0);
}

bool PartialPaymentState::isValidPayment(float payment, POSContext& context)
{
    bool returnType = true;

    if (context.getPaymentMethod() == "MBWAY" || context.getPaymentMethod() == "CARD")
    {
        if (isOverpaying(payment, context))
        {
            std::cout << std::endl
                      << "Cannot pay more than total value with this method. Please insert a new value" << std::endl;
            context.transitionToState(new PartialPaymentState);

            returnType = false;
        }
    }
    return returnType;
}