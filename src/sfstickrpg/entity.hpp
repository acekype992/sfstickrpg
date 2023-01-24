#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

enum class Direction { up, left, right, down };


class Entity : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
public:
    Entity() : texture_{nullptr}
    {}

    virtual ~Entity() = default;

    void setTexture(sf::Texture &texture) noexcept
    {
        texture_ = &texture;
        sprite_.setTexture(*texture_);
    }

    virtual void update() = 0;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        target.draw(sprite_, states);
    }

    sf::Sprite sprite_;
    sf::Texture *texture_;
};

#endif // ENTITY_HPP
