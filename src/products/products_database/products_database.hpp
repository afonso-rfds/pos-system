#pragma once

#include "products/products.hpp"

#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

// Singleton class
class ProductsDatabase
{
  public:
    // Deleted copy constructor and assignment operator to ensure singleton pattern
    ProductsDatabase(const ProductsDatabase&)            = delete;
    ProductsDatabase& operator=(const ProductsDatabase&) = delete;

    /// @brief Singleotn access
    /// @return Instance to sole object of ProductsDatabase
    static ProductsDatabase* getInstance();

    /// @brief Searches in the database for the product desired
    /// @param EAN13 database field to look for (uniquely identifying a product)
    /// @return Pointer to the specified product or nullptr in case product is not found
    Product* findProduct(const std::string& EAN13);

  private:
    // Private constructor for Singleton pattern
    ProductsDatabase();

    /// @brief Unique instance of singleton
    static ProductsDatabase* singletonInstance;

    /// @brief Connection to the database
    std::unique_ptr<SQLite::Database> productDatabase;

    /// @brief Path to the database
    const std::string productsDatabasePath;
};
