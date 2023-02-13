#ifndef MAP_BASE_HPP
#define MAP_BASE_HPP

#include "ackmatrix/matrix.hpp"
#include "tileset_base.hpp"

#include <SFML/Graphics/VertexArray.hpp>

class base_Map
{
public:
    base_Map(std::size_t width, std::size_t height, base_Tileset *tileset);
    virtual ~base_Map() noexcept = default;

//    virtual sf::IntRect getGlobalBounds() const noexcept = 0;

protected:
    sf::VertexArray& vertices() const noexcept;
    base_Tileset& tileset() const noexcept;

private:
    void setTileMap(const std::size_t x, const std::size_t y);

    ObserverPtr<base_Tileset> tileset_;
    ack::Matrix<std::size_t> map_;
    sf::VertexArray vertices_;
};

#endif // MAP_BASE_HPP
