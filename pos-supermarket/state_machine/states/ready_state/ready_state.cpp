#include "ready_state.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"
#include "state_machine/states/items_state/items_state.hpp"

#include <iostream>

void ReadyState::enterState(POSContext& context)
{
    context.getTransactionData().cleanPreviousTransactionData();

    do
    {
        std::cout << "--- Ready to start registering products ---" << std::endl;
        std::cout << "Press \"Enter\" to continue or type \"Cancel\" to go to the main menu" << std::endl;

        getUserInput();

    } while (userInput != "CANCEL" && !userInput.empty());
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