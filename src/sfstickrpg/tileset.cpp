#include "tileset.hpp"


Tileset::Tileset(size_type width, size_type height, const sf::Texture &texture)
    : tilesetTexture_ {texture}
    , tilesetSize_ {tilesetTexture_.getSize()}
    , tileSize_{width, height}
{
    sf::Vector2u matSize { tilesetSize_.x / tileSize_.x,
                           tilesetSize_.y / tileSize_.y};

    mat_.create(matSize.x, matSize.y);

    for(std::size_t y {0}; y < matSize.y; ++y)
        for(std::size_t x {0}; x < matSize.x; ++x)
        {
            sf::IntRect &tileRect = mat_(x,y);
            tileRect.left = x;
            tileRect.top  = y;
            tileRect.width = width;
            tileRect.height = height;

            tiles_.insert({tiles_.size(), tileRect});
        }
}


const sf::Texture& Tileset::getTexture() const noexcept
{
    return tilesetTexture_;
}


sf::Vector2u Tileset::getTilesetSize() const noexcept
{
    return tilesetSize_;
}


sf::Vector2u Tileset::getTileSize() const noexcept
{
    return tileSize_;
}


sf::IntRect Tileset::operator()(size_type x, size_type y) const noexcept
{
    return mat_(x,y);
}


sf::IntRect Tileset::operator[](size_type i) const  noexcept
{
    return tiles_.find(i)->second;
}


sf::Sprite Tileset::getDrawableTileset() const noexcept
{
    sf::Sprite sprite;
    sprite.setTexture(tilesetTexture_);

    return sprite;
}
