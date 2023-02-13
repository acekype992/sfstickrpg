#include "map_base.hpp"


base_Map::base_Map(std::size_t width, std::size_t height, base_Tileset *tileset)
    : tileset_ {tileset}
{
    assert(tileset && "tileset = nullptr");

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(width * height * 4);

    map_.create(width, height, 0);
    for(std::size_t y {0}; y < map_.rows(); ++y)
        for(std::size_t x {0}; x < map_.columns(); ++x)
            setTileMap(x, y);
}


sf::VertexArray& base_Map::vertices() const noexcept
{
    return const_cast<sf::VertexArray&>(vertices_);
}


base_Tileset& base_Map::tileset() const noexcept
{
    return *tileset_.get();
}


void base_Map::setTileMap(const std::size_t x, const std::size_t y)
{
    const std::size_t tw {tileset_->getTileSize().x};   // Tile width
    const std::size_t th {tileset_->getTileSize().y};   // Tile height
    const std::size_t ti {map_(x, y)};                  // Tile id
    const sf::IntRect tr {(*tileset_)[ti]};             // Texture rect texture on tileset

    // Tile :
    sf::Vertex *quad = &vertices_[(y * map_.columns() + x) * 4];

    quad[0].position = sf::Vector2f(x * tw     , y * th);
    quad[1].position = sf::Vector2f((x+1) * tw , y * th);
    quad[2].position = sf::Vector2f((x+1) * tw , (y+1) * th);
    quad[3].position = sf::Vector2f(x * tw     , (y+1) * th);

    quad[0].texCoords = sf::Vector2f(tr.left * tw     , tr.top * th);
    quad[1].texCoords = sf::Vector2f((tr.left+1) * tw , tr.top * th);
    quad[2].texCoords = sf::Vector2f((tr.left+1) * tw , (tr.top+1) * th);
    quad[3].texCoords = sf::Vector2f(tr.left * tw     , (tr.top+1) * th);
}
