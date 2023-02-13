#include "tileset.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Tileset::Tileset(sf::Texture &texture, sf::Vector2u tileSize)
    : base_Tileset {&texture, tileSize}
{

}


sf::IntRect Tileset::getGlobalBounds() const noexcept
{
    sf::IntRect rect;
    rect.width  = getTilesetSize().x;
    rect.height = getTilesetSize().y;
    rect.left   = sf::Transformable::getPosition().x;
    rect.top    = sf::Transformable::getPosition().y;

    return rect;
}


void Tileset::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &getTexture();

    target.draw(vertices(), states);
}

