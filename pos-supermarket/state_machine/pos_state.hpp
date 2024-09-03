#pragma once

#include <string>

// Forward declaration
class POSContext;

class POSState
{
  public:
    virtual ~POSState() = default;

    /// @brief Process the current state
    /// @param[inout] context Current state machine context
    virtual void processState(POSContext& context) = 0;

    /// @brief Logic to execute when entering the state for the first time
    /// @param[inout] context Current state machine context
    virtual void enterState(POSContext& context) = 0;

    /// @brief Logic to execute when leaving the state
    /// @param[inout] context Current state machine context
    virtual void exitState(POSContext& context) = 0;
};
