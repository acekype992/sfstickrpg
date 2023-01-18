#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <memory>
#include <stack>

#include "state.hpp"

class StateManager
{
public:
    StateManager() noexcept = default;
    ~StateManager() noexcept = default;

    void addState(std::unique_ptr<State> state, bool replace = false);
    void removeState();

    void process();

    std::unique_ptr<State>& currentState() noexcept;

private:
    std::stack<std::unique_ptr<State>> states_;
    std::unique_ptr<State> newState_;
    bool add_;
    bool replace_;
    bool remove_;
};

#endif // STATE_HPP
