#include "items_state.hpp"

#include "state_machine/states/payment/payment_selection_state/payment_selection_state.hpp"
#include "state_machine/states/ready_state/ready_state.hpp"

#include <iostream>

void ItemsState::enterState(POSContext& context)
{
    std::cout << "--- Transaction started ---\n";
    std::cout << "Enter EAN13 of the products you want to register.\n";
    std::cout << "Type \"Done\" to finish transaction or \"Cancel\" to go to the previous menu\n\n";
}

void ItemsState::processState(POSContext& context)
{
    do
    {
        std::cout << "[Done/Cancel/EAN13]: ";
        getUserInput();

        if (userInput == "DONE" || userInput == "CANCEL")
        {
            break;
        }

        const Product* product = databasesManager.findProduct(userInput);
        if (product != nullptr)
        {
            context.getTransactionData().addRegisteredProduct(*product);
            printRegisteredItems(context);
        }
        else
        {
            std::cout << "Invalid EAN13. Try again." << std::endl;
        }

    } while (userInput != "DONE" && userInput != "CANCEL");

    stateTransition(context);
}

void ItemsState::stateTransition(POSContext& context)
{
    if (userInput == "DONE")
    {
        // Prevent advancing without any products
        if (context.getTransactionData().getRegisteredProducts().empty())
        {
            context.transitionToState(new ItemsState());
        }
        else
        {
            context.transitionToState(new PaymentSelectionState());
        }
    }
    else
    {
        context.transitionToState(new ReadyState());
    }
}

void ItemsState::printRegisteredItems(POSContext& context) const
{
    const auto& products = context.getTransactionData().getRegisteredProducts();
    for (const auto& product : products)
    {
        float productPrice = product.second.second * product.second.first.price;
        std::cout
            << product.second.second << " x " << product.second.first.productName << ": " << productPrice << "€" << std::endl;
    }

    // Now print the registered items
    std::cout << "\nSubtotal: " << context.getTransactionData().getSubtotalPrice() << "€"
              << "\nTax: " << context.getTransactionData().getTaxPrice() << "€\n\n";
}
