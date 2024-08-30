#pragma once

#include <string>

// Forward declaration
class POSContext;  

class POSState 
{
public:
    virtual ~POSState() = default;

    virtual void handleInput(POSContext& context, const std::string& input) = 0;
    virtual void enterState(POSContext& context) = 0;  
    virtual void exitState(POSContext& context) = 0;   
};

