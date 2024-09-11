#include "payment_completion_state.hpp"

#include "invoice/invoice_database/invoice_database.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>

void PaymentCompletionState::enterState(POSContext& context)
{
    invoice = createInvoice(context);
    invoice->printInvoice();
}

void PaymentCompletionState::processState(POSContext& context)
{
    std::cout << "\nThanks for your purchase!\n";
    std::cout << "Save transaction, start new transaction or exit\n";

    do
    {
        std::cout << "[Save/Start/Exit]: ";
        getUserInput();

        if (userInput != "SAVE" && userInput != "START" && userInput != "EXIT")
        {
            std::cout << "\n\nInvalid Command. Try again.\n";
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

void PaymentCompletionState::saveTransaction(POSContext& context)
{
    InvoiceDatabase::getInstance()->addInvoice(*invoice);

    std::cout << "Transaction saved!\n";
    std::cout << "Start new transaction or exit\n";

    do
    {
        std::cout << "[Start/Exit]: ";
        getUserInput();

        if (userInput != "START" && userInput != "EXIT")
        {
            std::cout << "\n\nInvalid Command. Try again.\n";
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

    createdInvoice->registeredProducts     = context.getTransactionData().getRegisteredProducts();
    createdInvoice->storeIdentification    = context.getTransactionData().getStoreIdentification();
    createdInvoice->subtotalPrice          = context.getTransactionData().getSubtotalPrice();
    createdInvoice->taxPrice               = context.getTransactionData().getTaxPrice();
    createdInvoice->totalPrice             = createdInvoice->subtotalPrice + createdInvoice->taxPrice;
    createdInvoice->amountPaid             = context.getTransactionData().getSubtotalPrice() + context.getTransactionData().getTaxPrice() + context.getTransactionData().getCashChange();
    createdInvoice->cashChange             = context.getTransactionData().getCashChange();
    createdInvoice->operatorIdentification = context.getTransactionData().getCurrentOperator();
    createdInvoice->invoiceNumber          = generateInvoiceNumber();

    return createdInvoice;
}
