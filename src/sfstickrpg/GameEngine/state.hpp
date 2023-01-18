#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Window/Event.hpp>

using Event = sf::Event;

struct State
{
    virtual void initialize() = 0;
    virtual void processEvent(const Event &event) = 0;
    virtual void processEvent() {};
    virtual void draw() = 0;
    virtual void update(float dt) = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
};

#endif // STATE_HPP
