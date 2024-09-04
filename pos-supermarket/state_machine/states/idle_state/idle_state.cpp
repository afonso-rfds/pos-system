#include "idle_state.hpp"
#include "config.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include <algorithm>
#include <limits.h>
#include <regex>

void IdleState::enterState(POSContext& context)
{
    context.setCurrentOperator(""); // Assign no operator
    showWelcomeScreen();
}

void IdleState::exitState(POSContext& context)
{
    std::cout << "Operator '" << userInput << "' logged in." << std::endl
              << std::endl;
}

void IdleState::processState(POSContext& context)
{
    do
    {
        std::cout << "Please identify yourself: ";

        // In debug mode don't flush cin buffer
#ifndef DEBUG_MODE_ENABLED
        std::cin.ignore(INT_MAX, '\n');
#endif
        std::getline(std::cin, userInput);

        if (!isValidName(userInput))
        {
            std::cout << std::endl
                      << "Invalid name. Choose another." << std::endl;
        }

    } while (!isValidName(userInput));

    context.setCurrentOperator(userInput);
    context.transitionToState(new ReadyState());
}

void IdleState::showWelcomeScreen()
{
    do
    {
        std::cout << "---------- Welcome to the supermarket! ----------\n";
        std::cout << "Press \"Enter\" to start or type \"Exit\" to leave\n";

        // In debug mode don't flush cin buffer
#ifndef DEBUG_MODE_ENABLED
        std::cin.ignore(INT_MAX, '\n');
#endif
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

    } while (userInput != "EXIT" && !userInput.empty());

    if (userInput == "EXIT")
    {
        exit(EXIT_SUCCESS);
    }
}

bool IdleState::isValidName(std::string operatorsName)
{
    // Regex to match only alphabetic characters (both uppercase and lowercase)
    std::regex alphaRegex("^[A-Za-z]+$");

    // Return true if the input matches the regex, false otherwise
    return std::regex_match(operatorsName, alphaRegex);
}