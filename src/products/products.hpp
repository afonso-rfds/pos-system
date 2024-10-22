#pragma once

#include <string>

class Product
{
  public:
    Product()  = default;
    ~Product() = default;

    /// @brief EAN13 that uniquely identifies the product
    std::string EAN13;

    /// @brief Name of the product
    std::string productName;

    /// @brief Price of the product
    double price;

    /// @brief Tax rate associated with the product
    double taxRate;
};
