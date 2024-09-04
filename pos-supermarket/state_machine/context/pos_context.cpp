#include "pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

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

void POSContext::addRegisteredProduct(const Product& product)
{
    // Get reference to <std::pair>'Value' from 'Key' productName
    auto& productEntry = registeredProducts[product.EAN13];

    // If product is already in the map, increment the quantity
    if (productEntry.second > 0)
    {
        productEntry.second++;
    }
    else
    {
        // Otherwise, add the product with quantity 1
        productEntry = std::make_pair(product, 1);
    }

    // Update the total price
    currentTotalPrice += product.price * (1 + product.taxRate);
}

//**** -------------- Setters -------------- ****

void POSContext::setCurrentOperator(std::string operatorIdentifier)
{
    currentOperator = operatorIdentifier;
}

void POSContext::setTotalPrice(float transactionPrice)
{
    currentTotalPrice = transactionPrice;
}

//**** -------------- Getters -------------- ****

POSState* POSContext::getCurrentState() const
{
    return currentState.get();
}

const std::string POSContext::getCurrentOperator() const
{
    return currentOperator;
}

const float POSContext::getTotalPrice() const
{
    return currentTotalPrice;
}

const std::unordered_map<std::string, std::pair<Product, int>>& POSContext::getRegisteredProducts() const
{
    return registeredProducts;
}