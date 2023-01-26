#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <memory>
#include <unordered_map>

#include "ackmatrix/matrix.hpp"


class Tileset : public sf::NonCopyable
{
    using size_type = std::size_t;
public:
    Tileset(unsigned int width, unsigned int height, sf::Texture &texture);

    sf::Texture& getTexture() const noexcept;
    sf::Vector2u getTilesetSize() const noexcept;
    sf::Vector2u getTileSize() const noexcept;

    sf::IntRect operator()(size_type x, size_type y) const noexcept;
    sf::IntRect operator[](size_type i) const noexcept;

private:
    std::unique_ptr<sf::Texture> tilesetTexture_;
    const sf::Vector2u tilesetSize_;
    const sf::Vector2u tileSize_;

    std::unordered_map<std::size_t, sf::IntRect> tiles_;
    ack::Matrix<sf::IntRect> mat_;
};

#endif // TILESET_HPP
