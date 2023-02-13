#include "map.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Map::Map(sf::Vector2u size, base_Tileset *tileset)
    : base_Map {size.x, size.y, tileset}, Drawable {tileset->getTexture()}
{
    isBoundingRectVisible = true;
}


sf::IntRect Map::getGlobalBounds() const noexcept
{
    sf::IntRect rect {vertices().getBounds()};
    return rect;
}


void Map::initializeDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
{
    target.draw(vertices(), states);
}
