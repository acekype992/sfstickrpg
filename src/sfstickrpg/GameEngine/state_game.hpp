#ifndef STATE_GAME_HPP
#define STATE_GAME_HPP

#include <SFML/Window/Event.hpp>

using Event = sf::Event;
using KeyEvent = sf::Event::KeyEvent;
using MouseMoveEvent = sf::Event::MouseMoveEvent;
using MouseButtonEvent = sf::Event::MouseButtonEvent;
using SizeEvent  = sf::Event::SizeEvent;

#include "game_engine_data.hpp"
#include "state.hpp"

class StateGame : public State
{
public:
    StateGame(GameEngine::GameEngineData &gameEngineData) noexcept
        : assets   {gameEngineData.assets}
        , game     {gameEngineData.states}
        , window   {gameEngineData.window}
    {}

    virtual ~StateGame() = default;


    virtual void process_event() override
    {
        Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                keyPressEvent(event.key);
                break;
            case Event::KeyReleased:
                keyReleaseEvent(event.key);
                break;
            case Event::MouseMoved:
                mouseMoveEvent(event.mouseMove);
                break;
            case Event::MouseButtonPressed:
                mouseClickEvent(event.mouseButton);
                break;
            case Event::Resized:
                resizeEvent(event.size);
                break;
            default:
                break;
            }
        }
    }

    virtual void initialize() override = 0;
    virtual void pre_update() override = 0;
    virtual void update() override = 0;
    virtual void draw() override = 0;

protected:
    virtual void keyPressEvent(const KeyEvent &event) = 0;
    virtual void keyReleaseEvent(const KeyEvent &event) = 0;
    virtual void mouseMoveEvent(const MouseMoveEvent &event) = 0;
    virtual void mouseClickEvent(const MouseButtonEvent &event) = 0;
    virtual void resizeEvent(const SizeEvent &event) = 0;

    AssetManager& assets;
    StateManager& game;
    sf::RenderWindow& window;
};

#endif // STATE_GAME_HPP
