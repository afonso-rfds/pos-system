#pragma once

#include "invoice/invoice.hpp"

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

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

    /// @brief Opens the database connection
    void openDatabase();

    /// @brief Creates the necessary table in the database if they don't exist
    void createTable() const;

    /// @brief Retrieve an invoice from the database using the invoice number
    /// @param invoiceNumber The unique number of the invoice
    /// @return A pointer to the invoice if found, nullptr otherwise
    Invoice* getInvoice(const std::string& invoiceNumber) const;

    /// @brief Fetches an invoice from the query result
    /// @param query SQL query that retrieves the invoice
    /// @return Pointer to the populated Invoice object. nullptr otherwise
    Invoice* fetchInvoiceFromQuery(SQLite::Statement& query) const;

    /// @brief Verifies if the database exists and it's populated
    /// @return true if yes. false if it doesn't exist or is empty
    bool isDatabaseValid() const;

    /// @brief Unique instance of singleton
    static InvoiceDatabase* singletonInstance;

    /// @brief Connection to the database
    std::unique_ptr<SQLite::Database> invoiceDatabase;

    /// @brief Path to the database
    const std::string invoiceDatabasePath;
};
