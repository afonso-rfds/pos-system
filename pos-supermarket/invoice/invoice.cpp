#include "invoice.hpp"

#include "iostream"

void Invoice::printInvoice() const
{
    std::cout << "\n*---------------------------------*" << std::endl;
    std::cout << "*----------- Invoice -------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "    Store: " << storeIdentification << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << std::endl;

    printRegisteredItems();
    printData();
}

void Invoice::printSavedData() const
{
    std::cout << "\n*---------------------------------*" << std::endl;
    std::cout << "*----------- Invoice -------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "    Store: " << storeIdentification << std::endl;
    std::cout << "*---------------------------------*" << std::endl;

    printData();
}

void Invoice::printRegisteredItems() const
{
    const auto& products = registeredProducts;

    for (const auto& product : products)
    {
        std::cout << "          ";
        float productPrice = product.second.second * product.second.first.price;
        std::cout
            << product.second.second << " x " << product.second.first.productName << ": " << productPrice << "€" << std::endl;
    }
}

void Invoice::printData() const
{
    // Now print the registered items
    std::cout << "  Subtotal: " << subtotalPrice << "€"
              << std::endl
              << "  Tax:      " << taxPrice << "€" << std::endl
              << "  Total:    " << totalPrice << "€" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "  Paid:     " << amountPaid << "€" << std::endl;
    std::cout << "  Change:   " << cashChange << "€" << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
    std::cout << "  Operator: " << operatorIdentification << std::endl;
    std::cout << "  Invoice number: " << invoiceNumber << std::endl;
    std::cout << "*---------------------------------*" << std::endl;
}