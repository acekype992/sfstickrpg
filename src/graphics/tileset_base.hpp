#ifndef TILESET_BASE_HPP
#define TILESET_BASE_HPP

#include "core/observerptr.hpp"

#include "ackmatrix/matrix.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class base_Tileset
{
public:
    base_Tileset(sf::Texture *texture, const sf::Vector2u &tileSize);
    virtual ~base_Tileset() noexcept = default;

    void setTileset(sf::Texture *texture, const sf::Vector2u &tileSize);

    sf::Texture& getTexture() const noexcept;
    sf::Vector2u getTilesetSize() const noexcept;
    sf::Vector2u getTileSize() const noexcept;

    sf::IntRect operator[](std::size_t index) const noexcept;

    virtual sf::IntRect getGlobalBounds() const noexcept = 0;

protected:
    sf::VertexArray &vertices() const noexcept;
    sf::IntRect& tiles(std::size_t x, std::size_t y) noexcept;

    virtual void initialize_tileset(const ack::Matrix<sf::IntRect> &tilesetMatrix);

private:
    ObserverPtr<sf::Texture> tilesetTexture_;
    sf::Vector2u tileSize_;

    sf::VertexArray vertices_;
    ack::Matrix<sf::IntRect> tilesRect_;
    std::vector<sf::IntRect> tiles_;

};

#endif // TILESET_BASE_HPP
