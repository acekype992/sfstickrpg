#include "drawable.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Drawable::Drawable(sf::Texture &texture) noexcept
    : texture_ {&texture}
    , isVisible {true}
    , isBoundingRectVisible {false}
{

}


sf::IntRect Drawable::getGlobalBounds() const noexcept
{
    return sf::IntRect(vertices_.getBounds());
}


void Drawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(isVisible)
    {
        states.transform *= getTransform();
        states.texture = texture_.get();
        initializeDraw(target, states);
        if(isBoundingRectVisible)
        {
            sf::RectangleShape r;
            r.setFillColor(sf::Color::Transparent);
            r.setOutlineColor(sf::Color::Red);
            r.setOutlineThickness(1);
            r.setSize(sf::Vector2f(getGlobalBounds().getSize()));
            r.setPosition(sf::Vector2f(getGlobalBounds().getPosition()));
            target.draw(r, states);
        }

    }
}
