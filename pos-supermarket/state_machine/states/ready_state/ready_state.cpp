#include "ready_state.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"
#include "state_machine/states/items_state/items_state.hpp"

#include <iostream>

void ReadyState::enterState(POSContext& context)
{
    context.getTransactionData().cleanPreviousTransactionData();

    do
    {
        std::cout << "\n--- Ready to start registering products ---" << std::endl;
        std::cout << "Press \"Enter\" to continue or type \"Menu\" to go to the main menu" << std::endl;

        getUserInput();

    } while (userInput != "MENU" && !userInput.empty());
}

void ReadyState::processState(POSContext& context)
{
    if (userInput == "MENU")
    {
        context.transitionToState(StateType::Idle);
    }
    else
    {
        context.transitionToState(StateType::Items);
    }
}