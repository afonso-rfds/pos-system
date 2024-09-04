#pragma once

#include <string>

class Product
{
  public:
    Product()  = default;
    ~Product() = default;

    std::string EAN13;
    std::string name;
    double price;
    double taxRate;
};
