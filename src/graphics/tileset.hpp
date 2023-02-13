#ifndef TILESET_HPP
#define TILESET_HPP

#include "tileset_base.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class Tileset : public base_Tileset, public sf::Drawable, public sf::Transformable
{
public:
    Tileset(sf::Texture &texture, sf::Vector2u tileSize);
    virtual ~Tileset() noexcept = default;

    virtual sf::IntRect getGlobalBounds() const noexcept override;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif // TILESET_HPP
