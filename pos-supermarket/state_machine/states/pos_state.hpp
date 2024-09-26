#pragma once

#include <string>

// Forward declaration
class Context;

class POSState
{
  public:
    virtual ~POSState() = default;

    /// @brief Process the current state
    /// @param[inout] context Current state machine context
    virtual void processState(Context& context) = 0;

    /// @brief Logic to execute when entering the state for the first time
    /// @param[inout] context Current state machine context
    virtual void enterState(Context& context) = 0;
};
