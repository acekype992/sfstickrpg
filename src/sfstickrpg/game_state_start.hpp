#ifndef GAME_STATE_START
#define GAME_STATE_START

#include <SFML/Graphics/Sprite.hpp>

#include "game_state.hpp"


class GameEngineData;

class GameStateStart : public GameStateBase
{
public:
    using GameStateBase::GameStateBase;

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
    sf::View view_;
    sf::Sprite background_;
};


#endif // GAME_STATE_START
