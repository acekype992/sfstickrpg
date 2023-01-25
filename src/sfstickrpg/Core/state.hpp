#ifndef STATE_HPP
#define STATE_HPP

struct State
{
    virtual void initialize() = 0;
    virtual void process_event() = 0;
    virtual void draw() = 0;
    virtual void pre_update() = 0;
    virtual void update() = 0;
};

#endif // STATE_HPP
