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
    remainingToPay = currentSubtotalPrice + currentTaxPrice;

    // Round to 2 decimals
    currentSubtotalPrice = std::floor(currentSubtotalPrice * 100.0f) / 100.0f;
    currentTaxPrice      = std::floor(currentTaxPrice * 100.0f) / 100.0f;
    remainingToPay       = std::floor(remainingToPay * 100.0f) / 100.0f;
}

void POSContext::cleanPreviousTransactionData()
{
    currentSubtotalPrice = 0;
    currentTaxPrice      = 0;
    remainingToPay       = 0;
    change               = 0;
    paymentMethod        = "";
    registeredProducts.clear();
}

//**** -------------- Setters -------------- ****

void POSContext::setCurrentOperator(std::string operatorIdentifier)
{
    currentOperator = operatorIdentifier;
}

void POSContext::setRemainingToPay(float paymentLeft)
{

    if (paymentLeft > 0 && paymentLeft < 0.01) // Fault tolerance due to float type
    {
        remainingToPay = 0;
    }
    else
    {
        remainingToPay = paymentLeft;
    }
}

void POSContext::setPaymentMethod(const std::string& methodToPay)
{
    paymentMethod = methodToPay;
}

void POSContext::setCashChange(const float changeToSet)
{
    change = changeToSet;
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

const float POSContext::getRemainingToPay() const
{
    return remainingToPay;
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

const std::string& POSContext::getPaymentMethod() const
{
    return paymentMethod;
}

float POSContext::getCashChange()
{
    change = std::floor(change * 100.0f) / 100.0f;
    return change;
}

std::string POSContext::getStoreIdentification()
{
    return storeIdentification;
}
