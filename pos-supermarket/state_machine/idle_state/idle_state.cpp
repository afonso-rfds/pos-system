#include <algorithm>
#include <regex>

#include "idle_state.hpp"

void IdleState::enterState(POSContext& context)
{
    showWelcomeScreen();
}

void IdleState::exitState(POSContext& context)
{
    std::cout << "Operator " << userInput << " logged in." << std::endl;
}

void IdleState::processState(POSContext& context)
{
    do
    {
        std::cout << "Please identify yourself: ";
        std::cin >> userInput;
        std::cout << std::endl;

        if (!isValidName(userInput))
        {
            std::cout << std::endl
                      << "Invalid name. Choose another." << std::endl;
        }

    } while (!isValidName(userInput));

    context.transitionToState(new ReadyState());
}

void IdleState::showWelcomeScreen()
{
    do
    {
        std::cout << "----- Welcome to the supermarket! -----\n";
        std::cout << "Press \"Enter\" to start or type \"Exit\" to leave\n";

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