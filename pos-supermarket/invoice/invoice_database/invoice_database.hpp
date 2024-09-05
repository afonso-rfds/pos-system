#pragma once

#include "invoice/invoice.hpp"

#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <unordered_map>

const std::string INVOICE_DATABASE_PATH = "/home/afonso/workspace/pos-exercise/pos-supermarket/database/invoices.db";

class InvoiceDatabase
{
  public:
    /// @brief Delete copy constructor and assignment operator to prevent copies
    InvoiceDatabase(const InvoiceDatabase&)            = delete;
    InvoiceDatabase& operator=(const InvoiceDatabase&) = delete;

    /// @brief Destructor
    ~InvoiceDatabase() = default;

    /// @brief Get the singleton instance of the InvoiceDatabase
    /// @return Instance to sole object of InvoiceDatabase
    static InvoiceDatabase* getInstance();

    /// @brief Add a new invoice to the database
    /// @param invoice Invoice to be added
    void addInvoice(const Invoice& invoice);

    /// @brief Print all invoices stored in the database
    void printAllInvoices() const;

    /// @brief Remove all invoices from the database
    void removeAllInvoices();

  private:
    /// @brief Private constructor for Singleton pattern
    InvoiceDatabase();

    /// @brief Retrieve an invoice from the database using the invoice number
    /// @param invoiceNumber The unique number of the invoice
    /// @return A pointer to the invoice if found, nullptr otherwise
    Invoice* getInvoice(const std::string& invoiceNumber) const;

    /// @brief Unique instance of singleton
    static InvoiceDatabase* singletonInstance;

    /// @brief Connection to the database
    std::unique_ptr<SQLite::Database> invoiceDatabase;

    /// @brief Flag to track if the database is open
    bool openStatus = false;
};
