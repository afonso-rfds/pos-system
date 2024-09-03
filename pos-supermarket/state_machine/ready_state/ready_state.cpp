#include "ready_state.hpp"
#include "config.hpp"
#include "state_machine/idle_state/idle_state.hpp"
#include "state_machine/items_state/items_state.hpp"

#include <algorithm>
#include <limits.h>

void ReadyState::enterState(POSContext& context)
{
    showWelcomeScreen();
}

void ReadyState::exitState(POSContext& context)
{
}

void ReadyState::processState(POSContext& context)
{
    if (userInput == "CANCEL")
    {
        context.transitionToState(new IdleState());
    }
    else
    {
        context.transitionToState(new ItemsState());
    }
}

void ReadyState::showWelcomeScreen()
{
    do
    {
        std::cout << "--- Ready to start registering products ---" << std::endl;
        std::cout << "Press \"Enter\" to continue or type \"Cancel\" to go to the previous menu" << std::endl;

#ifndef DEBUG_MODE_ENABLED
        std::cin.ignore(INT_MAX, '\n');
#endif

        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
        std::cout << std::endl
                  << std::endl;

    } while (userInput != "CANCEL" && !userInput.empty());
}
