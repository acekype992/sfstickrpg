#ifndef TILESET_HPP
#define TILESET_HPP

#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "ackmatrix/matrix.hpp"

class Tileset
{
public:
    Tileset();
    explicit Tileset(unsigned int width, unsigned int height, sf::Texture &texture);

    sf::Texture& getTexture() const;
    sf::IntRect operator()(unsigned int x, unsigned int y) const;

    sf::Vector2u getTileSize() const;

private:
    unsigned int tileWidth_;
    unsigned int tileHeight_;

    std::unique_ptr<sf::Texture> tileset_;
    ack::Matrix<sf::IntRect> mat_;

};

#endif // TILESET_HPP
