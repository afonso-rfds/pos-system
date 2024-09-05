#pragma once

#include "products/products.hpp"

#include <memory>
#include <string>
#include <unordered_map>

class Invoice
{
  public:
    Invoice()  = default;
    ~Invoice() = default;

    /// @brief Print the whole invoice
    void printInvoice() const;

    /// @brief Print saved invoice data
    void printSavedData() const;

    /// @brief Print the registered items
    void printRegisteredItems() const;

    /// @brief Print data such as total, change, operator, invoice number, etc
    void printData() const;

    /// @brief Products registered so far in the transaction, mapped by product name or identifier
    /// @note Key - Value pair in which Value is a std::pair composed of Product and number of ocurrences of this product
    /// @param string Product EAN13 (Apple, Eggs, ...)
    /// @param Product[Value.first]  Product to insert
    /// @param     int[Value.second] Number of ocurrences of Product so far
    std::unordered_map<std::string, std::pair<Product, int>> registeredProducts;

    /// @brief Store identification
    std::string storeIdentification;

    /// @brief Subtotal of the transaction
    float subtotalPrice;

    /// @brief Tax price of the transaction
    float taxPrice;

    /// @brief Total of the transaction
    float totalPrice;

    /// @brief How much it was paid
    float amountPaid;

    /// @brief Payment with cash greater than required ( change)
    float cashChange;

    /// @brief Operator of the transaction
    std::string operatorIdentification;

    /// @brief Invoice Number
    std::string invoiceNumber;
};
