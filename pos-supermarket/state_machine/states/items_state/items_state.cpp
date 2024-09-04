#include "items_state.hpp"

#include "config.hpp"
#include "products/products_database/products_database.hpp"
#include "state_machine/states/payment_states/payment_selection_state/payment_selection_state.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include "iostream"
#include <algorithm>
#include <limits.h>

void ItemsState::enterState(POSContext& context)
{
    std::cout << "--- Transaction started ---" << std::endl;
    std::cout << "Enter EAN13 of the products you want to register." << std::endl;
    std::cout << "Type \"Done\" to finish transaction or \"Cancel\" to go to the previous menu" << std::endl;
}

void ItemsState::exitState(POSContext& context)
{
}

void ItemsState::processState(POSContext& context)
{
    do
    {
        std::cout << "EAN: ";
        getUserInput();

        if (userInput == "DONE" || userInput == "CANCEL")
        {
            break;
        }

        const Product* product = ProductsDatabase::getInstance()->findProduct(userInput);
        if (product != nullptr)
        {
            context.addRegisteredProduct(*product);
            printRegisteredItems(context);
        }
        else
        {
            std::cout << "Invalid EAN13. Try again." << std::endl;
        }

    } while (userInput != "DONE" && userInput != "CANCEL");

    stateTransition(context);
}

void ItemsState::getUserInput()
{
    //  In debug mode don't flush cin buffer
#ifndef DEBUG_MODE_ENABLED
    std::cin.ignore(INT_MAX, '\n');
#endif
    std::getline(std::cin, userInput);
    std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    std::cout << std::endl
              << std::endl;
}

void ItemsState::stateTransition(POSContext& context)
{
    if (userInput == "DONE")
    {
        context.transitionToState(new PaymentSelectionState());
    }
    else
    {
        context.transitionToState(new ReadyState());
    }
}

void ItemsState::printRegisteredItems(POSContext& context) const
{
    const auto& products = context.getRegisteredProducts();
    for (const auto& product : products)
    {
        float productPrice = product.second.second * product.second.first.price;
        std::cout
            << product.second.second << " x " << product.second.first.productName << ": " << productPrice << "€" << std::endl;
    }

    // Now print the registered items
    std::cout << std::endl
              << "Subtotal: " << context.getSubtotalPrice() << "€"
              << std::endl
              << "Tax: " << context.getTaxPrice() << "€"
              << std::endl
              << std::endl;
}
