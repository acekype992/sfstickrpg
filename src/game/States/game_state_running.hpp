#ifndef GAME_STATE_RUNNING_HPP
#define GAME_STATE_RUNNING_HPP

#include <unordered_map>

#include "Core/state_game.hpp"
#include "Entities/player_entity.hpp"

#include "map.hpp"


class GameStateRunning : public StateGame
{
    void loadMaps();

public:
    using StateGame::StateGame;
    ~GameStateRunning() noexcept = default;

    virtual void initialize() override;
    virtual void pre_update() override;
    virtual void update() override;
    virtual void draw() override;

private:
    void movePlayer();

protected:
    void keyPressEvent(const Event::KeyEvent &event) override;
    void keyReleaseEvent(const Event::KeyEvent &event) override;
    void mouseMoveEvent(const Event::MouseMoveEvent &event) override;
    void mouseClickEvent(const Event::MouseButtonEvent &event) override;
    void resizeEvent(const Event::SizeEvent &event) override;

    bool keyPressed_;
    std::unique_ptr<sf::Event::KeyEvent> lastKeyPressed_;

private:
    sf::View gameView_;
    float gameViewZoom_;

    std::unordered_map<std::string, Map> mapByString_;
    Map *currentMap_;

    PlayerEntity player_;
};

#endif // GAME_STATE_RUNNING_HPP
