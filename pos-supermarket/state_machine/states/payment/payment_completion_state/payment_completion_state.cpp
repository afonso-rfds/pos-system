#include "payment_completion_state.hpp"
#include "config.hpp"
#include "iostream"
#include "state_machine/states/ready_state/ready_state.hpp"
#include <algorithm>
#include <invoice/invoice_database/invoice_database.hpp>
#include <limits.h>

#include <chrono>
#include <iomanip>
#include <random>
#include <sstream>

void PaymentCompletionState::enterState(POSContext& context)
{
    invoice = createInvoice(context);
    //  context.setInvoiceNumber(generateInvoiceNumber());
    invoice->printInvoice();
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

void PaymentCompletionState::saveTransaction(POSContext& context)
{
    InvoiceDatabase::getInstance()->addInvoice(*invoice);

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

Invoice* PaymentCompletionState::createInvoice(POSContext& context)
{
    Invoice* createdInvoice                = new Invoice();

    createdInvoice->registeredProducts     = context.getRegisteredProducts();
    createdInvoice->storeIdentification    = context.getStoreIdentification();
    createdInvoice->subtotalPrice          = context.getSubtotalPrice();
    createdInvoice->taxPrice               = context.getTaxPrice();
    createdInvoice->totalPrice             = createdInvoice->subtotalPrice + createdInvoice->taxPrice;
    createdInvoice->amountPaid             = context.getSubtotalPrice() + context.getTaxPrice() + context.getCashChange();
    createdInvoice->cashChange             = context.getCashChange();
    createdInvoice->operatorIdentification = context.getCurrentOperator();
    createdInvoice->invoiceNumber          = generateInvoiceNumber();

    return createdInvoice;
}
