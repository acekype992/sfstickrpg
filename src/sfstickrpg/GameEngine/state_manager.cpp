#include <cassert>
#include "state_manager.hpp"


void StateManager::add_state(std::unique_ptr<State> state, bool replace) noexcept
{
    newState_ = std::move(state);
    add_ = true;
    replace_ = replace;
}


void StateManager::remove_state() noexcept
{
    remove_ = true;
}


std::unique_ptr<State>& StateManager::current_state()
{
    assert(!states_.empty() && "states_ is empty || no state defined");

    return states_.top();
}


void StateManager::process()
{
    if(remove_ && !states_.empty())
    {
        remove_state();
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
