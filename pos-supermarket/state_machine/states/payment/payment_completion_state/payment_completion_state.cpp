#include "payment_completion_state.hpp"
#include "config.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include "iostream"
#include <algorithm>
#include <limits.h>

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>

void PaymentCompletionState::enterState(POSContext& context)
{
    context.setInvoiceNumber(generateInvoiceNumber());
    printInvoice(context);
}

void PaymentCompletionState::exitState(POSContext& context)
{
}

void PaymentCompletionState::processState(POSContext& context)
{
    std::cout << std::endl
              << "Thanks for your purchase!" << std::endl;
    std::cout << "Save transaction, start new transaction or exit" << std::endl;

    do
    {
        std::cout << "[Save/Start/Exit]: ";
        getUserInput();

        if (userInput != "SAVE" && userInput != "START" && userInput != "EXIT")
        {
            std::cout << std::endl
                      << std::endl
                      << "Invalid Command. Try again." << std::endl;
        }
    } while (userInput != "SAVE" && userInput != "START" && userInput != "EXIT");

    if (userInput == "SAVE")
    {
        saveTransaction(context);
    }
    else if (userInput == "START")
    {
        context.transitionToState(new ReadyState());
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

void PaymentCompletionState::getUserInput()
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

void PaymentCompletionState::printInvoice(POSContext& context)
{
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "*----------- Invoice -------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "    Store: " << context.getStoreIdentification() << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << std::endl;

    printRegisteredItems(context);
    printData(context);
}

void PaymentCompletionState::printRegisteredItems(POSContext& context) const
{
    const auto& products = context.getRegisteredProducts();

    for (const auto& product : products)
    {
        std::cout << "          ";
        float productPrice = product.second.second * product.second.first.price;
        std::cout
            << product.second.second << " x " << product.second.first.productName << ": " << productPrice << "€" << std::endl;
    }
}

void PaymentCompletionState::printData(POSContext& context) const
{
    // Now print the registered items
    std::cout << std::endl
              << "  Subtotal: " << context.getSubtotalPrice() << "€"
              << std::endl
              << "  Tax:      " << context.getTaxPrice() << "€" << std::endl
              << "  Total:    " << context.getSubtotalPrice() + context.getTaxPrice() << "€" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "  Paid:     " << context.getSubtotalPrice() + context.getTaxPrice() + context.getCashChange() << "€" << std::endl;
    std::cout << "  Change:   " << context.getCashChange() << "€" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "  Operator: " << context.getCurrentOperator() << std::endl;
    std::cout << "  Invoice number: " << context.getInvoiceNumber() << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
}

void PaymentCompletionState::saveTransaction(POSContext& context)
{
    std::cout << "Transaction saved!" << std::endl;
    std::cout << "Start new transaction or exit" << std::endl;

    do
    {
        std::cout << "[Start/Exit]: ";
        getUserInput();

        if (userInput != "START" && userInput != "EXIT")
        {
            std::cout << std::endl
                      << std::endl
                      << "Invalid Command. Try again." << std::endl;
        }
    } while (userInput != "START" && userInput != "EXIT");

    if (userInput == "START")
    {
        context.transitionToState(new ReadyState());
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

std::string PaymentCompletionState::generateInvoiceNumber()
{
    // Get current time since epoch (in seconds)
    std::time_t now = std::time(0);

    // Use rand() to generate random numbers
    int randomPart = rand() % 1000;  // Generate a number between 0 and 999
    int uniquePart = now % 10000000; // To ensure a 7-digit timestamp-based part

    // Combine to make a 10-digit number
    std::ostringstream oss;
    oss << std::setw(7) << std::setfill('0') << uniquePart
        << std::setw(3) << std::setfill('0') << randomPart;

    return oss.str();
}
