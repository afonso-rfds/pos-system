#include "pos_context.hpp"
#include "pos_state.hpp"

POSContext::POSContext(POSState* initialState) : currentState(initialState)
{
    currentState->enterState(*this);
}

void POSContext::setState(POSState* newState)
{
    currentState.reset(newState); // Clean up the old state and switch to the new one
    currentState->enterState(*this);
}

void POSContext::processCurrentState()
{
    currentState->processState(*this);
}

void POSContext::transitionToState(POSState* newState)
{
    currentState->exitState(*this);
    setState(newState);
}

POSState* POSContext::getCurrentState()
{
    return currentState.get();
}
