#include "idle_state.hpp"

#include "state_machine/states/ready_state/ready_state.hpp"

#include <iostream>
#include <regex>

void IdleState::enterState(POSContext& context)
{
    context.getTransactionData().setCurrentOperator(""); // Assign no operator

    do
    {
        std::cout << "\n---------- Welcome to the supermarket! ----------\n";
        std::cout << "Press \"Enter\" to start or type \"Exit\" to leave\n";
        std::cout << "Type \"Show\" see saved invoices or type \"Clean\" to remove all invoices\n";
        std::cout << "\n[Enter/Exit/Show/Clean]: ";

        getUserInput();

    } while (userInput != "EXIT" && !userInput.empty() && userInput != "SHOW" && userInput != "CLEAN");

    if (userInput == "EXIT")
    {
        exit(EXIT_SUCCESS);
    }
}

void IdleState::processState(POSContext& context)
{
    if (userInput == "SHOW")
    {
        databasesManager.printAllInvoices();
        context.transitionToState(StateType::Idle);
    }
    else if (userInput == "CLEAN")
    {
        databasesManager.removeAllInvoices();
        context.transitionToState(StateType::Idle);
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
        std::cout << "\nPlease identify yourself: ";
        getUserInput();

        if (!isValidName(userInput))
        {
            std::cout << "--- Invalid name ---\n";
            std::cout << "Please choose another.\n";
        }

    } while (!isValidName(userInput));

    context.getTransactionData().setCurrentOperator(userInput);
    std::cout << "Operator '" << userInput << "' logged in.\n\n";
    context.transitionToState(StateType::Ready);
}