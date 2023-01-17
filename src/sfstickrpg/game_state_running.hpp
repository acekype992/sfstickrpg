#ifndef GAME_STATE_RUNNING_HPP
#define GAME_STATE_RUNNING_HPP

#include "game_state.hpp"

class GameStateRunning : public GameStateBase
{
public:
    using GameStateBase::GameStateBase;
    ~GameStateRunning() noexcept = default;

    virtual void initialize() override;
    virtual void draw() override;
    virtual void update(float dt) override;

    virtual void pause() override;
    virtual void resume() override;

protected:
    void keyPressEvent(const Event::KeyEvent &event) override;
    void keyReleaseEvent(const Event::KeyEvent &event) override;
    void mouseMoveEvent(const Event::MouseMoveEvent &event) override;
    void mouseClickEvent(const Event::MouseButtonEvent &event) override;
    void resizeEvent(const Event::SizeEvent &event) override;

private:
};

#endif // GAME_STATE_RUNNING_HPP
