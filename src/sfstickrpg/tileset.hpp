#ifndef TILESET_HPP
#define TILESET_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <memory>
#include <unordered_map>

#include "ackmatrix/matrix.hpp"


class Tileset
{
    using size_type = unsigned int;

public:
    Tileset(sf::Vector2u tileSize, const std::string &filename);

    ~Tileset() noexcept = default;

    Tileset(const Tileset&) = delete;
    Tileset& operator=(const Tileset&) = delete;

    sf::Texture& getTexture() const noexcept;
    sf::Vector2u getTilesetSize() const noexcept;
    sf::Vector2u getTileSize() const noexcept;

    sf::Sprite getDrawableTileset() const noexcept;

    sf::IntRect operator()(size_type x, size_type y) const noexcept;
    sf::IntRect operator[](size_type i) const noexcept;

private:
    std::unique_ptr<sf::Texture> texture_;
    sf::Vector2u tilesetSize_;
    sf::Vector2u tileSize_;

    std::unordered_map<std::size_t, sf::IntRect> tiles_;
    ack::Matrix<sf::IntRect> tilesMat_;
};

#endif // TILESET_HPP
