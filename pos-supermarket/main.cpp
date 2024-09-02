#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "state_machine/idle_state/idle_state.hpp"
#include "state_machine/pos_context.hpp"

int main()
{

    POSContext posContext(new IdleState());
    posContext.processCurrentState();

    return 0;
}