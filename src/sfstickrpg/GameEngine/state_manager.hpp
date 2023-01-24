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

    void add_state(std::unique_ptr<State> state, bool replace = false) noexcept;
    void remove_state() noexcept;
    void process();

    std::unique_ptr<State>& current_state();

private:
    std::stack<std::unique_ptr<State>> states_;
    std::unique_ptr<State> newState_;
    bool add_;
    bool replace_;
    bool remove_;
};

#endif // STATE_HPP
