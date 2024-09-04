#include <iostream>
#include <sqlite3.h>
#include <string.h>

#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"

int main()
{

    POSContext posContext(new IdleState());

    while (true)
    {
        posContext.processCurrentState();
    }

    return 0;
}