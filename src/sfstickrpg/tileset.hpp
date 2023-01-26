#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>
#include <unordered_map>

#include "ackmatrix/matrix.hpp"


class Tileset
{
    using size_type = unsigned int;
public:
    Tileset(size_type width, size_type height, const sf::Texture &texture);

    const sf::Texture &getTexture() const noexcept;
    sf::Vector2u getTilesetSize() const noexcept;
    sf::Vector2u getTileSize() const noexcept;

    sf::IntRect operator()(size_type x, size_type y) const noexcept;
    sf::IntRect operator[](size_type i) const noexcept;

    sf::Sprite getDrawableTileset() const noexcept;

private:
    const sf::Texture &tilesetTexture_;
    const sf::Vector2u tilesetSize_;
    const sf::Vector2u tileSize_;

    std::unordered_map<std::size_t, sf::IntRect> tiles_;
    ack::Matrix<sf::IntRect> mat_;
};

#endif // TILESET_HPP
