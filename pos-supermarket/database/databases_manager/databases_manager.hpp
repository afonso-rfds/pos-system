#pragma once

#include "invoice/invoice.hpp"
#include "invoice/invoice_database/invoice_database.hpp"
#include "products/products.hpp"
#include "products/products_database/products_database.hpp"

class DatabasesManager
{
  public:
    /// @brief Searches in the products database for the product desired
    /// @param EAN13 database field to look for (uniquely identifying a product)
    /// @return Pointer to the specified product or nullptr in case product is not found
    Product* findProduct(const std::string& EAN13);

    /// @brief Add a new invoice to the database
    /// @param invoice Invoice to be added
    void addInvoice(const Invoice& invoice);

    /// @brief Print all invoices stored in the invoices database
    void printAllInvoices();

    /// @brief Remove all invoices from the invoices database
    void removeAllInvoices();
};