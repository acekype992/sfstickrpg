#include <cassert>
#include "state_manager.hpp"


void StateManager::addState(std::unique_ptr<State> state, bool replace)
{
    newState_ = std::move(state);
    add_ = true;
    replace_ = replace;
}


void StateManager::removeState()
{
    remove_ = true;
}


std::unique_ptr<State>& StateManager::currentState() noexcept
{
    assert(!states_.empty() && "states_ is empty || no state defined");

    return states_.top();
}


void StateManager::process()
{
    if(remove_ && !states_.empty())
    {
        removeState();
        remove_ = false;
    }

    if(add_)
    {
        if(!states_.empty())
        {
            if(replace_)
            {
                states_.pop();
            }
        }
        states_.push(std::move(newState_));
        states_.top()->initialize();
        add_ = false;
    }
}
