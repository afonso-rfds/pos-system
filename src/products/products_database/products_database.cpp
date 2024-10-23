#include "products_database.hpp"

/// @brief Initialization must be done outside to prevent race conditions (in case threads are used)
ProductsDatabase* ProductsDatabase::singletonInstance = nullptr;

ProductsDatabase::ProductsDatabase()
{
    std::string currentFile                = std::string(__FILE__);
    std::string baseDirectory              = currentFile.substr(0, currentFile.find("src/products"));
    const std::string productsDatabasePath = baseDirectory + "src/database/products.db";

    productDatabase.reset(new SQLite::Database(productsDatabasePath, SQLite::OPEN_READONLY));
}

ProductsDatabase* ProductsDatabase::getInstance()
{
    if (singletonInstance == nullptr)
    {
        singletonInstance = new ProductsDatabase();
    }
    return singletonInstance;
}

Product* ProductsDatabase::findProduct(const std::string& EAN13)
{
    Product* product = nullptr;

    // Compile a SQL query
    SQLite::Statement query(*productDatabase, "SELECT ean13, name, price, tax_rate FROM products WHERE ean13 = ?");

    // Bind the EAN13 code to the first parameter of SQL query (EAN field)
    query.bind(1, EAN13);

    // Execute the query and check if a result is found
    if (query.executeStep())
    {
        // Create a Product object and populate its fields with the query result
        product              = new Product();

        product->EAN13       = query.getColumn(0).getString();
        product->productName = query.getColumn(1).getString();
        product->price       = query.getColumn(2).getDouble();
        product->taxRate     = query.getColumn(3).getDouble();
    }

    return product; // Return nullptr if no product is found
}
