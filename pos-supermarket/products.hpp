#pragma once

#include <string>

class Product
{
  public:
    Product()  = default;
    ~Product() = default;

    std::string EAN13;
    std::string productName;
    double price;
    double taxRate;
};
