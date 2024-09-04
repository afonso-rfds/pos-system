#include "pos_context.hpp"
#include "state_machine/states/pos_state.hpp"

#include <cmath>

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

    updatePrice(product);
}

void POSContext::updatePrice(const Product& product)
{
    // Calculate Subtotal price (price without tax), tax and total price
    currentSubtotalPrice += product.price;
    currentTaxPrice += product.price * product.taxRate;

    // Round to 2 decimals
    currentSubtotalPrice = std::round(currentSubtotalPrice * 100.0) / 100.0;
    currentTaxPrice      = std::round(currentTaxPrice * 100.0) / 100.0;

    currentTotalPrice    = currentSubtotalPrice + currentTaxPrice;
}

void POSContext::cleanPreviousTransactionData()
{
    currentSubtotalPrice = 0;
    currentTaxPrice      = 0;
    currentTotalPrice    = 0;
    registeredProducts.clear();
}

//**** -------------- Setters -------------- ****

void POSContext::setCurrentOperator(std::string operatorIdentifier)
{
    currentOperator = operatorIdentifier;
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

const float POSContext::getSubtotalPrice() const
{
    return currentSubtotalPrice;
}

const float POSContext::getTaxPrice() const
{
    return currentTaxPrice;
}

const std::unordered_map<std::string, std::pair<Product, int>>& POSContext::getRegisteredProducts() const
{
    return registeredProducts;
}