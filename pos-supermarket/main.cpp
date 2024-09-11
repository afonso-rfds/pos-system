#include "state_machine/context/pos_context.hpp"
#include "state_machine/states/idle_state/idle_state.hpp"

int main()
{

    POSContext posContext(new IdleState(), "Afonso's Supermarket");

    while (true)
    {
        posContext.processCurrentState();
    }

    return 0;
}