#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "tileset.hpp"


class Entity : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
public:
    enum class Direction { up, left, right, down };

    virtual ~Entity() = default;

    void initialize(const Tileset &tileset) noexcept
    {
        tileset_ = &tileset;
        sprite_.setTexture(tileset_->getTexture());
    }

    void setMapPosition(int x, int y)
    {
        x *= tileset_->getTileSize().x;
        y *= tileset_->getTileSize().y;
        sf::Transformable::setPosition(x, y);
    }

    sf::Vector2i getMapPosition() const
    {
        sf::Vector2i position {sf::Transformable::getPosition()};
        position.x /= tileset_->getTileSize().x;
        position.y /= tileset_->getTileSize().y;
        return position;
    }

    sf::FloatRect getBoundingRect() const noexcept
    {
        return sprite_.getGlobalBounds();
    }

    virtual void update() = 0;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(sprite_, states);
    }

    sf::Sprite sprite_;
    const Tileset *tileset_;

};

#endif // ENTITY_HPP
