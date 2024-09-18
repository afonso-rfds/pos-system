#include "state_machine/context/pos_context.hpp"

int main()
{
    POSContext posContext("Afonso's Supermarket");

    while (true)
    {
        posContext.processCurrentState();
    }

    return 0;
}