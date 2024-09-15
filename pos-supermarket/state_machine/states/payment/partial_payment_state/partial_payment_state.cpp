#include "partial_payment_state.hpp"

#include "state_machine/states/payment/payment_completion_state/payment_completion_state.hpp"
#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"

#include <iostream>
#include <regex>

void PartialPaymentState::enterState(POSContext& context)
{
    if (context.getTransactionData().getPaymentMethod() == "MBWAY")
    {
        std::cout << "MBWay: ";
    }
    else if (context.getTransactionData().getPaymentMethod() == "CARD")
    {
        std::cout << "Card: ";
    }
    else
    {
        std::cout << "Cash: ";
    }
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
        context.transitionToState(StateType::PaymentCompletion);
    }
    else
    {
        context.transitionToState(StateType::PaymentSelection);
    }
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
    std::cout << "\n\nInvalid Number. Please try again.\n";
    enterState(context);
    getUserInput();
}

bool PartialPaymentState::isOverpaying(float payment, POSContext& context)
{
    return payment > context.getTransactionData().getRemainingToPay();
}

void PartialPaymentState::updateRemainingToPay(float payment, POSContext& context)
{
    if (isOverpaying(payment, context))
    {
        context.getTransactionData().setCashChange(payment - context.getTransactionData().getRemainingToPay());
        context.getTransactionData().setRemainingToPay(0);
    }
    else
    {
        context.getTransactionData().setRemainingToPay(context.getTransactionData().getRemainingToPay() - payment);
    }
}

bool PartialPaymentState::isPaymentComplete(POSContext& context)
{
    return (context.getTransactionData().getRemainingToPay() == 0);
}

bool PartialPaymentState::isValidPayment(float payment, POSContext& context)
{
    bool returnType = true;

    if (context.getTransactionData().getPaymentMethod() == "MBWAY" || context.getTransactionData().getPaymentMethod() == "CARD")
    {
        if (isOverpaying(payment, context))
        {
            std::cout << "\nCannot pay more than total value with this method. Please insert a new value\n";
            context.transitionToState(StateType::PartialPayment);

            returnType = false;
        }
    }
    return returnType;
}