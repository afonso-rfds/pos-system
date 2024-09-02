#include <algorithm>
#include <regex>

#include "idle_state.hpp"

void IdleState::enterState(POSContext& context)
{
    showWelcomeScreen();
}

void IdleState::exitState(POSContext& context)
{
    std::cout << "Operator " << m_userInput << " logged in." << std::endl;
}

void IdleState::processState(POSContext& context)
{
    do
    {
        std::cout << "Please identify yourself: ";
        std::cin >> m_userInput;
        std::cout << std::endl;

        if (!isValidName(m_userInput))
        {
            std::cout << std::endl
                      << "Invalid name. Choose another." << std::endl;
        }

    } while (!isValidName(m_userInput));

    context.transitionToState(new ReadyState());
}

void IdleState::showWelcomeScreen()
{
    do
    {
        std::cout << "----- Welcome to the supermarket! -----\n";
        std::cout << "Press \"Enter\" to start or type \"Exit\" to leave\n";

        std::getline(std::cin, m_userInput);
        std::transform(m_userInput.begin(), m_userInput.end(), m_userInput.begin(), ::toupper);

    } while (m_userInput != "EXIT" && !m_userInput.empty());

    if (m_userInput == "EXIT")
    {
        exit(EXIT_SUCCESS);
    }
}

bool IdleState::isValidName(std::string userInput)
{
    // Regex to match only alphabetic characters (both uppercase and lowercase)
    std::regex alphaRegex("^[A-Za-z]+$");

    // Return true if the input matches the regex, false otherwise
    return std::regex_match(userInput, alphaRegex);
}