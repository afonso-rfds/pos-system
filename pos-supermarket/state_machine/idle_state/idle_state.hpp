#pragma once

#include <string.h>

#include "iostream"
#include "state_machine/pos_context.hpp"
#include "state_machine/pos_state.hpp"
#include "state_machine/ready_state/ready_state.hpp"

class IdleState : public POSState
{
  public:
    IdleState()  = default;
    ~IdleState() = default;

    void enterState(POSContext& context) override;
    void exitState(POSContext& context) override;
    void processState(POSContext& context) override;

  private:
    void showWelcomeScreen();

    bool isValidName(std::string userInput);

    std::string m_userInput;
};
