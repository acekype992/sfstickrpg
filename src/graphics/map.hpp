#ifndef MAP_HPP
#define MAP_HPP

#include "map_base.hpp"
#include "graphics/drawable.hpp"

class Map : public base_Map, public Drawable
{
public:
    Map(sf::Vector2u size, base_Tileset *tileset);
    virtual ~Map() noexcept = default;

    virtual sf::IntRect getGlobalBounds() const noexcept override;

protected:
    virtual void initializeDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

private:
    sf::RectangleShape boundingRect_;
};


#endif // MAP_HPP

