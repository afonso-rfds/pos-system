#pragma once

#include "products/products.hpp"
#include "state_machine/states/pos_state.hpp"

class ItemsState : public POSState
{
  public:
    ItemsState()  = default;
    ~ItemsState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    /// @brief Gets input from the user
    void getUserInput();

    /// @brief Transition to the previous/next state
    /// @param context Current state machine context
    void stateTransition(POSContext& context);

    /// @brief Print the registered items
    /// @param context Current state machine context
    void printRegisteredItems(POSContext& context) const;

    /// @brief Commands from the user
    std::string userInput;
};
