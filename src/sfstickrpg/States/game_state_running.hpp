#ifndef GAME_STATE_RUNNING_HPP
#define GAME_STATE_RUNNING_HPP

#include "Core/state_game.hpp"

#include <unordered_map>

#include "map.hpp"

class GameStateRunning : public StateGame
{
public:
    using StateGame::StateGame;
    ~GameStateRunning() noexcept = default;

    virtual void initialize() override;
    virtual void pre_update() override;
    virtual void update() override;
    virtual void draw() override;

protected:
    void keyPressEvent(const Event::KeyEvent &event) override;
    void keyReleaseEvent(const Event::KeyEvent &event) override;
    void mouseMoveEvent(const Event::MouseMoveEvent &event) override;
    void mouseClickEvent(const Event::MouseButtonEvent &event) override;
    void resizeEvent(const Event::SizeEvent &event) override;

private:
    sf::View gameView_;
    float gameViewZoom_;

    std::unordered_map<std::string, Map> mapByString_;
    Map *currentMap_;
};

#endif // GAME_STATE_RUNNING_HPP
