#ifndef INVOICES_DATABASE_HPP
#define INVOICES_DATABASE_HPP

#include "product.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <memory>
#include <string>
#include <unordered_map>

class InvoicesDatabase
{
  public:
    // Deleted copy constructor and assignment operator to ensure singleton pattern
    InvoicesDatabase(const InvoicesDatabase&)            = delete;
    InvoicesDatabase& operator=(const InvoicesDatabase&) = delete;

    /// @brief Singleton access
    /// @return Instance to sole object of InvoicesDatabase
    static InvoicesDatabase* getInstance();

    // Method to save an invoice
    bool saveInvoice(const std::string& invoiceNumber, const std::string& operatorId, float subtotal, float tax, float total, const std::unordered_map<std::string, std::pair<Product, int>>& products, float cashChange);

    // Method to retrieve an invoice (will be useful in another state)
    std::unordered_map<std::string, std::pair<Product, int>> getInvoice(const std::string& invoiceNumber);

  private:
    // Constructor is private to enforce singleton pattern
    InvoicesDatabase();

    // SQLite database pointer
    std::unique_ptr<SQLite::Database> invoiceDatabase;

    // Static singleton instance
    static InvoicesDatabase* singletonInstance;
};

#endif // INVOICES_DATABASE_HPP
