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

    //**** -------------- Setters -------------- ****

    /// @brief Set current operator's identifier
    /// @param currentOperator operator's identifier
    void setCurrentOperator(std::string operatorIdentifier);

    /// @brief Get current transaction price
    /// @return Current transaction price
    void setTotalPrice(float transactionPrice);

    //**** -------------- Getters -------------- ****

    /// @brief Get current active state instance
    /// @return Pointer to current active state
    POSState* getCurrentState() const;

    /// @brief Get current operator's identifier
    /// @return Current operator's identifier
    const std::string getCurrentOperator() const;

    /// @brief Get current transaction price
    /// @return Current transaction price
    const float getTotalPrice() const;

    /// @brief Get the map of registered products with their quantities
    /// @return Reference to the map of registered products
    const std::unordered_map<std::string, std::pair<Product, int>>& getRegisteredProducts() const;

  private:
    /// @brief Set new state
    /// @param[in] newState New active state
    void setState(POSState* newState);

    /// @brief Current active state
    std::unique_ptr<POSState> currentState;

    /// @brief Current operator executing transactions
    std::string currentOperator;

    /// @brief Price of the current active transaction
    float currentTotalPrice;

    /// @brief Products registered so far in the transaction, mapped by product name or identifier
    /// @note Key - Value pair in which Value is a std::pair composed of Product and number of ocurrences of this product
    /// @param string Product EAN13 (Apple, Eggs, ...)
    /// @param Product[Value.first]  Product to insert
    /// @param     int[Value.second] Number of ocurrences of Product so far
    std::unordered_map<std::string, std::pair<Product, int>> registeredProducts;
};
