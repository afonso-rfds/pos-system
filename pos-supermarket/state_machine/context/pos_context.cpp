#include "pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

#include <cmath>

POSContext::POSContext(POSState* initialState, std::string storeIdentifier) : currentState(initialState), transactionData(storeIdentifier)
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
    setState(newState);
}

//**** -------------- Getters -------------- ****

POSState* POSContext::getCurrentState() const
{
    return currentState.get();
}

TransactionData& POSContext::getTransactionData()
{
    return transactionData;
}
