#ifndef STATE_MAP_EDITOR
#define STATE_MAP_EDITOR

#include "Core/state_game.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#include "tileset.hpp"
#include "map.hpp"


class StateMapEditor : public StateGame
{
public:
    using StateGame::StateGame;
    ~StateMapEditor() noexcept = default;

    virtual void initialize() override;
    virtual void pre_update() override;
    virtual void update() override;
    virtual void draw() override;

protected:
    void keyPressEvent(const Event::KeyEvent &event) override;
    void keyReleaseEvent(const Event::KeyEvent &event) override;
    void mouseMoveEvent(const Event::MouseMoveEvent &event) override;
    void mouseClickEvent(const Event::MouseButtonEvent &event) override;
    void mouseReleaseEvent(const MouseButtonEvent &event) override;
    void resizeEvent(const Event::SizeEvent &event) override;

private:
    Tileset *tileset_;
    sf::Sprite tilesetSprite_;

    std::unique_ptr<Map> map_;
    sf::View viewMap_;
    float viewMapZoom_;

    sf::RenderWindow windowTileset_;
    sf::View viewTileset_;

    sf::IntRect r;

    sf::RectangleShape recShape_;
    sf::RectangleShape tilShape_;
    bool drawRecShape_;
    bool drawTilShape_;

    bool mousePressed_;

};


#endif // STATE_MAP_EDITOR
