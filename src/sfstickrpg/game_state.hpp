#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "game_engine_data.hpp"
#include "state.hpp"

using KeyEvent = sf::Event::KeyEvent;
using MouseMoveEvent = sf::Event::MouseMoveEvent;
using MouseButtonEvent = sf::Event::MouseButtonEvent;
using SizeEvent  = sf::Event::SizeEvent;


class _GameStateBase : public State
{
public:
    virtual void processEvent(const Event &event) override
    {
        switch(event.type)
        {
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

    virtual void initialize() override = 0;
    virtual void draw() override = 0;
    virtual void update(float dt) override = 0;

    virtual void pause() override {}
    virtual void resume() override {}

protected:
    virtual void keyPressEvent(const Event::KeyEvent &event) = 0;
    virtual void keyReleaseEvent(const Event::KeyEvent &event) = 0;
    virtual void mouseMoveEvent(const Event::MouseMoveEvent &event) = 0;
    virtual void mouseClickEvent(const Event::MouseButtonEvent &event) = 0;
    virtual void resizeEvent(const Event::SizeEvent &event) = 0;

};


class GameStateBase : public _GameStateBase
{
public:
    GameStateBase(std::shared_ptr<GameEngineData> gameEngineData) noexcept
        : engineData_ {gameEngineData} {}

    virtual ~GameStateBase() = default;

    virtual void initialize() override = 0;
    virtual void draw() override = 0;
    virtual void update(float dt) override = 0;

    virtual void pause() override {}
    virtual void resume() override {}

    virtual void processEvent(const Event &event) override {}
    virtual void processEvent() override
    {
        Event event;
        while(engineData_->window.pollEvent(event))
        {
            switch(event.type)
            {
            case Event::Closed:
                engineData_->window.close();
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

protected:
    Window& window() noexcept { return engineData_->window; }

    AssetManager& assets() noexcept { return engineData_->assets; }

    StateManager& game() noexcept { return engineData_->states; }

    virtual void keyPressEvent(const Event::KeyEvent &event) override = 0;
    virtual void keyReleaseEvent(const Event::KeyEvent &event) override = 0;
    virtual void mouseMoveEvent(const Event::MouseMoveEvent &event) override = 0;
    virtual void mouseClickEvent(const Event::MouseButtonEvent &event) override = 0;
    virtual void resizeEvent(const Event::SizeEvent &event) override = 0;

private:
    std::shared_ptr<GameEngineData> engineData_;
};

#endif // GAME_STATE_HPP
