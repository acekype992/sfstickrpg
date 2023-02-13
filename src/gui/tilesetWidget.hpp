#ifndef TILESET_WIDGET_HPP
#define TILESET_WIDGET_HPP

#include "core/eventHandling.hpp"
#include "graphics/tileset.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

class TilesetWidget : public Tileset, public EventHandling
{
public:
    TilesetWidget(sf::Texture& texture, const sf::Vector2u &tileSize, sf::RenderWindow &window);

    sf::Time getUpdateTime() const noexcept override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void keyPressEvent(const KeyEvent &event) override;
    void keyReleaseEvent(const KeyEvent &event) override;
    void mouseClickEvent(const MouseButtonEvent &event, sf::RenderWindow &window) override;
    void mouseReleaseEvent(const MouseButtonEvent &event) override;
    void mouseMoveEvent(const MouseMoveEvent &event, sf::RenderWindow &window) override;
    void windowResizeEvent(const SizeEvent &event, sf::RenderWindow &window) override;

private:
    bool isVisible_;
    bool isTileHoverVisible_;
    sf::RectangleShape tileHovered_;
    sf::RectangleShape focusedTile_;
    sf::RectangleShape boundingRect_;

    sf::View view_;
};

#endif // TILESET_WIDGET_HPP
