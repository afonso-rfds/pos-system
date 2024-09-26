#pragma once

#include "database/databases_manager/databases_manager.hpp"
#include "products/products.hpp"
#include "state_machine/states/pos_base_state.hpp"

class ItemsState : public BaseState
{
  public:
    ItemsState()  = default;
    ~ItemsState() = default;

    void enterState(Context& context) override;
    void processState(Context& context) override;

  private:
    /// @brief Transition to the previous/next state
    /// @param context Current state machine context
    void stateTransition(Context& context);

    /// @brief Print the registered items
    /// @param context Current state machine context
    void printRegisteredItems(Context& context) const;

    /// @brief Member that deals with the databases
    DatabasesManager databasesManager;
};
