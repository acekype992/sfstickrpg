#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "tileset.hpp"


class Map : public sf::Drawable, public sf::Transformable
{
    using size_type = std::size_t;

public:
    Map(Tileset &tileset, const std::string &filename);
    Map(Tileset &tileset, size_type w, size_type h);

    ~Map() noexcept = default;

    void setTile(size_type x, size_type y, sf::IntRect rect);

    sf::FloatRect getBoundingRect() const noexcept;
    sf::Vector2u getSize() const noexcept;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Tileset &tileset_;
    sf::VertexArray vertices_;
    ack::Matrix<size_type> mapMatrix_;
public:
    std::vector<sf::IntRect> tilesRect_;

};

#endif // MAP_HPP
