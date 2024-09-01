#pragma once

#include "pos_state.hpp"
#include <memory>

class POSContext
{
  public:
    POSContext(POSState* initialState);
    ~POSContext() = default;

    /// @brief Delegate input handling to the current state
    /// @param[in] input User input
    void handleInput(const std::string& input);

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    void transitionToState(POSState* newState);

    /// @brief Transition to a new state (exit current and enter new one)
    /// @param[in] newState New active state
    /// @return Pointer to current active state
    POSState* getCurrentState();

  private:
    /// @brief Set new state
    /// @param[in] newState New active state
    void setState(POSState* newState);

    std::unique_ptr<POSState> currentState;
};
