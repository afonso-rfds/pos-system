#include "state_machine/transaction_data/transaction_data.hpp"

#include <cmath>

void TransactionData::addRegisteredProduct(const Product& product)
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

void TransactionData::updatePrice(const Product& product)
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

void TransactionData::cleanPreviousTransactionData()
{
    currentSubtotalPrice = 0;
    currentTaxPrice      = 0;
    remainingToPay       = 0;
    change               = 0;
    paymentMethod        = "";
    registeredProducts.clear();
}

//**** -------------- Setters -------------- ****

void TransactionData::setCurrentOperator(std::string operatorIdentifier)
{
    currentOperator = operatorIdentifier;
}

void TransactionData::setRemainingToPay(float paymentLeft)
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

void TransactionData::setPaymentMethod(const std::string& methodToPay)
{
    paymentMethod = methodToPay;
}

void TransactionData::setCashChange(const float changeToSet)
{
    change = changeToSet;
}

//**** -------------- Getters -------------- ****

const std::string TransactionData::getCurrentOperator() const
{
    return currentOperator;
}

const float TransactionData::getRemainingToPay() const
{
    return remainingToPay;
}

const float TransactionData::getSubtotalPrice() const
{
    return currentSubtotalPrice;
}

const float TransactionData::getTaxPrice() const
{
    return currentTaxPrice;
}

const std::unordered_map<std::string, std::pair<Product, int>>& TransactionData::getRegisteredProducts() const
{
    return registeredProducts;
}

const std::string& TransactionData::getPaymentMethod() const
{
    return paymentMethod;
}

float TransactionData::getCashChange()
{
    change = std::floor(change * 100.0f) / 100.0f;
    return change;
}

std::string TransactionData::getStoreIdentification()
{
    return storeIdentification;
}
