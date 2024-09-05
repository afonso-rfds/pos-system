#pragma once

#include "products/products.hpp"
#include "state_machine/states/pos_state.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class POSContext
{
  public:
    POSContext(POSState* initialState);
    ~POSContext() = default;

    /// @brief Process the current active state
    void processCurrentState();

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    void transitionToState(POSState* newState);

    /// @brief Add or update a product in the map of registered products
    /// @param product Product to add
    void addRegisteredProduct(const Product& product);

    /// @brief Clears previous stored transaction data
    void cleanPreviousTransactionData();

    //**** -------------- Setters -------------- ****

    /// @brief Set current operator's identifier
    /// @param currentOperator operator's identifier
    void setCurrentOperator(std::string operatorIdentifier);

    /// @brief Set remaining to pay value
    /// @param paymentLeft remaining to pay value
    void setRemainingToPay(float paymentLeft);

    /// @brief Set the selected payment method
    /// @param paymentMethod Chosen payment method
    void setPaymentMethod(const std::string& methodToPay);

    /// @brief Set the cash change (payment with cash greater than required)
    /// @param changeToSet Change
    void setCashChange(const float changeToSet);

    //**** -------------- Getters -------------- ****

    /// @brief Get current active state instance
    /// @return Pointer to current active state
    POSState* getCurrentState() const;

    /// @brief Get current operator's identifier
    /// @return Current operator's identifier
    const std::string getCurrentOperator() const;

    /// @brief Get remaining to pay value
    /// @return Remaining to pay value
    const float getRemainingToPay() const;

    /// @brief Get current subtotal price
    /// @return Current subtotal price
    const float getSubtotalPrice() const;

    /// @brief Get current tax price
    /// @return Current tax price
    const float getTaxPrice() const;

    /// @brief Get the map of registered products with their quantities
    /// @return Reference to the map of registered products
    const std::unordered_map<std::string, std::pair<Product, int>>&
    getRegisteredProducts() const;

    /// @brief Get the selected payment method
    /// @return Payment method chosen
    const std::string& getPaymentMethod() const;

    /// @brief Get the cash change (payment with cash greater than required)
    /// @return Change
    float getCashChange();

  private:
    /// @brief Set new state
    /// @param[in] newState New active state
    void setState(POSState* newState);

    /// @brief Calculate current prices (subtotal, tax and total)
    /// @param product Product to add
    void updatePrice(const Product& product);

    /// @brief Current active state
    std::unique_ptr<POSState> currentState;

    /// @brief Current operator executing transactions
    std::string currentOperator;

    /// @brief Price of the current active transaction
    float remainingToPay = 0;

    /// @brief Price of the current active transaction
    float currentSubtotalPrice = 0;

    /// @brief Price of the current active transaction
    float currentTaxPrice = 0;

    /// @brief Payment with cash greater than required (needs to return change)
    float change = 0;

    /// @brief Products registered so far in the transaction, mapped by product name or identifier
    /// @note Key - Value pair in which Value is a std::pair composed of Product and number of ocurrences of this product
    /// @param string Product EAN13 (Apple, Eggs, ...)
    /// @param Product[Value.first]  Product to insert
    /// @param     int[Value.second] Number of ocurrences of Product so far
    std::unordered_map<std::string, std::pair<Product, int>> registeredProducts;

    /// @brief Payment method selected by the user
    std::string paymentMethod;
};
