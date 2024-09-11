#include "idle_state.hpp"

#include "invoice/invoice_database/invoice_database.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include <iostream>
#include <regex>

void IdleState::enterState(POSContext& context)
{
    context.setCurrentOperator(""); // Assign no operator

    do
    {
        std::cout << "---------- Welcome to the supermarket! ----------\n";
        std::cout << "Press \"Enter\" to start or type \"Exit\" to leave\n";
        std::cout << "Type \"Show\" see saved invoices or type \"Clean\" to remove all invoices\n";
        std::cout << "[Enter/Exit/Show/Clean]: ";

        getUserInput();

        std::cout << std::endl;

    } while (userInput != "EXIT" && !userInput.empty() && userInput != "SHOW" && userInput != "CLEAN");

    if (userInput == "EXIT")
    {
        exit(EXIT_SUCCESS);
    }
}

void IdleState::exitState(POSContext& context)
{
}

void IdleState::processState(POSContext& context)
{
    if (userInput == "SHOW")
    {
        InvoiceDatabase::getInstance()->printAllInvoices();
        context.transitionToState(new IdleState());
    }
    else if (userInput == "CLEAN")
    {
        InvoiceDatabase::getInstance()->removeAllInvoices();
        context.transitionToState(new IdleState());
        return;
    }
    else
    {
        processTransaction(context);
    }
}

bool IdleState::isValidName(std::string operatorsName)
{
    // Regex to match only alphabetic characters (both uppercase and lowercase)
    std::regex alphaRegex("^[A-Za-z]+$");

    // Return true if the input matches the regex, false otherwise
    return std::regex_match(operatorsName, alphaRegex);
}

void IdleState::processTransaction(POSContext& context)
{
    do
    {
        std::cout << "Please identify yourself: ";
        getUserInput();

        if (!isValidName(userInput))
        {
            std::cout << "\nInvalid name. Choose another.\n";
        }

    } while (!isValidName(userInput));

    context.setCurrentOperator(userInput);
    std::cout << "Operator '" << userInput << "' logged in.\n\n";
    context.transitionToState(new ReadyState());
}