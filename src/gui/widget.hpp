#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/Graphics/View.hpp>

class Widget
        : public sf::Drawable, public sf::Transformable
{
public:
    Widget();
    virtual ~Widget() noexcept = default;

    virtual sf::IntRect getGlobalBounds() const = 0;

protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;

private:
    sf::View view_;
};

#endif // WIDGET_HPP
