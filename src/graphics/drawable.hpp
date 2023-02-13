#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "core/observerptr.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Drawable : public sf::Drawable, public sf::Transformable
{
public:
    Drawable(sf::Texture &texture) noexcept;
    virtual ~Drawable() = default;

    virtual sf::IntRect getGlobalBounds() const noexcept;
protected:
    virtual void initializeDraw(sf::RenderTarget &target, const sf::RenderStates &states) const = 0;

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    ObserverPtr<sf::Texture> texture_;
    sf::VertexArray vertices_;
    sf::View view_;

public:
    bool isVisible;
    bool isBoundingRectVisible;
};

#endif // DRAWABLE_HPP
