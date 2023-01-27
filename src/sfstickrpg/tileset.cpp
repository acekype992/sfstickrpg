#include "tileset.hpp"


Tileset::Tileset(sf::Vector2u tileSize, const std::string &filename)
{
    texture_ = std::make_unique<sf::Texture>();
    if(!texture_->loadFromFile(filename))
        throw std::runtime_error("Cannot open file for tileset");

    tilesetSize_ = texture_->getSize();
    tileSize_ = tileSize;

    sf::Vector2u matSize { tilesetSize_.x / tileSize_.x,
                           tilesetSize_.y / tileSize_.y};

    tilesMat_.create(matSize.x, matSize.y);

    for(std::size_t y {0}; y < matSize.y; ++y)
        for(std::size_t x {0}; x < matSize.x; ++x)
        {
            sf::IntRect &tileRect = tilesMat_(x,y);
                tileRect.left   = x;
                tileRect.top    = y;
                tileRect.width  = tileSize_.x;
                tileRect.height = tileSize_.y;

            tiles_.insert({tiles_.size(), tileRect});
        }
}


sf::Texture& Tileset::getTexture() const noexcept
{
    return *texture_.get();
}


sf::Vector2u Tileset::getTilesetSize() const noexcept
{
    return tilesetSize_;
}


sf::Vector2u Tileset::getTileSize() const noexcept
{
    return tileSize_;
}


sf::Sprite Tileset::getDrawableTileset() const noexcept
{
    sf::Sprite sprite;
    sprite.setTexture(*texture_);

    return std::move(sprite);
}


sf::IntRect Tileset::operator()(size_type x, size_type y) const noexcept
{
    return tilesMat_(x,y);
}


sf::IntRect Tileset::operator[](size_type i) const  noexcept
{
    return tiles_.find(i)->second;
}

