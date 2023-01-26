#include "map.hpp"


Map::Map(const std::string &filename, const Tileset &tileset)
    : tileset_ {tileset}
{
    matrix_t mx;
    mx.loadFromFile(filename);

    const size_type tw {tileset_.getTileSize().x};
    const size_type th {tileset_.getTileSize().y};

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(tw * th * 4);
    for(std::size_t y {0}; y < mx.rows(); ++y)
        for(std::size_t x {0}; x < mx.columns(); ++x)
        {
            size_type tIndex = mx(x,y);
            sf::IntRect tr = tileset_[tIndex];

            sf::Vertex *quad = &vertices_[(y * mx.columns() + x) * 4];

            quad[0].position = sf::Vector2f(x * tw     , y * th);
            quad[1].position = sf::Vector2f((x+1) * tw , y * th);
            quad[2].position = sf::Vector2f((x+1) * tw , (y+1) * th);
            quad[3].position = sf::Vector2f(x * tw     , (y+1) * th);

            quad[0].texCoords = sf::Vector2f(tr.left * tw     , tr.top * th);
            quad[1].texCoords = sf::Vector2f((tr.left+1) * tw , tr.top * th);
            quad[2].texCoords = sf::Vector2f((tr.left+1) * tw , (tr.top+1) * th);
            quad[3].texCoords = sf::Vector2f(tr.left * tw     , (tr.top+1) * th);
        }
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileset_.getTexture();
    target.draw(vertices_, states);
}
