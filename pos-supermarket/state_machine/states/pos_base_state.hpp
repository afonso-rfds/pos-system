#pragma once

#include "iostream"
#include "state_machine/states/pos_state.hpp"

#include <algorithm>
#include <limits.h>
#include <string.h>

class BaseState : public POSState
{
  public:
    BaseState()          = default;
    virtual ~BaseState() = default;

  protected:
    /// @brief Gets input from the user
    void getUserInput()
    {
        std::getline(std::cin, userInput);
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
    }

    /// @brief Commands from the user
    std::string userInput;
};
