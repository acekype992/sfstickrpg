#include "tileset_base.hpp"


base_Tileset::base_Tileset(sf::Texture *texture, const sf::Vector2u &tileSize)
{
    vertices_.setPrimitiveType(sf::Quads);

    setTileset(texture, tileSize);
}


void base_Tileset::setTileset(sf::Texture *texture, const sf::Vector2u &tileSize)
{
    assert(tileSize.x > 0 && tileSize.y > 0 && "The tile size is invalid");

    tilesetTexture_ = ObserverPtr<sf::Texture>(texture);
    tileSize_ = tileSize;

    const sf::Vector2u matrixSize { getTilesetSize().x / tileSize_.x,
                                    getTilesetSize().y / tileSize_.y};

    tilesRect_.create(matrixSize.x, matrixSize.y);
    vertices_.resize(matrixSize.x * matrixSize.y * 4);

    initialize_tileset(tilesRect_);
}


sf::Texture& base_Tileset::getTexture() const noexcept
{
    return *tilesetTexture_.get();
}


sf::Vector2u base_Tileset::getTilesetSize() const noexcept
{
    return tilesetTexture_->getSize();
}


sf::Vector2u base_Tileset::getTileSize() const noexcept
{
    return tileSize_;
}


sf::IntRect base_Tileset::operator [](std::size_t index) const noexcept
{
    return tiles_[index];
}


sf::VertexArray &base_Tileset::vertices() const noexcept
{
    return const_cast<sf::VertexArray&>(vertices_);
}


sf::IntRect& base_Tileset::tiles(std::size_t x, std::size_t y) noexcept
{
    return tilesRect_(x, y);
}


void base_Tileset::initialize_tileset(const ack::Matrix<sf::IntRect> &tilesetMatrix)
{
    for(std::size_t y {0}; y < tilesetMatrix.rows(); ++y)
        for(std::size_t x {0}; x < tilesetMatrix.columns(); ++x)
        {
            sf::IntRect &tr = tiles(x,y);
                tr.left   = x;
                tr.top    = y;
                tr.width  = tileSize_.x;
                tr.height = tileSize_.y;

            sf::Vertex *quad = &vertices()[(y * tilesetMatrix.columns() + x) * 4];

            quad[0] = sf::Vector2f(x * tr.width     , y * tr.height);
            quad[1] = sf::Vector2f((x+1) * tr.width , y * tr.height);
            quad[2] = sf::Vector2f((x+1) * tr.width , (y+1) * tr.height);
            quad[3] = sf::Vector2f(x * tr.width     , (y+1) * tr.height);

            quad[0].texCoords = sf::Vector2f(tr.left * tr.width     , tr.top * tr.height);
            quad[1].texCoords = sf::Vector2f((tr.left+1) * tr.width , tr.top * tr.height);
            quad[2].texCoords = sf::Vector2f((tr.left+1) * tr.width , (tr.top+1) * tr.height);
            quad[3].texCoords = sf::Vector2f(tr.left * tr.width     , (tr.top+1) * tr.height);

            tiles_.push_back(tr);
        }
}
