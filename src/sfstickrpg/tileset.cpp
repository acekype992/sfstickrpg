#include "tileset.hpp"



Tileset::Tileset()
{

}


Tileset::Tileset(unsigned int width, unsigned int height, sf::Texture &texture)
    : tileWidth_ {width}
    , tileHeight_ {height}
    , tileset_ {std::make_unique<sf::Texture>(texture)}
{
    const sf::Vector2u txSize {tileset_->getSize()};
    sf::Vector2u matSize { txSize.x / tileWidth_, txSize.y / tileHeight_};
    mat_.create(matSize.x, matSize.y);

    for(std::size_t y {0}; y < matSize.y; ++y)
    {
        for(std::size_t x {0}; x < matSize.x; ++x)
        {
            auto& rect = mat_(x,y);
              rect = sf::IntRect(x,
                                 y,
                                 tileWidth_,
                                 tileHeight_);
        }
    }
}


sf::Texture& Tileset::getTexture() const
{
    return *tileset_.get();
}


sf::IntRect Tileset::operator ()(unsigned int x, unsigned int y) const
{
    sf::IntRect textureRect {mat_(x,y)};
    return std::move(textureRect);
}


sf::Vector2u Tileset::getTileSize() const
{
    return sf::Vector2u(tileWidth_, tileHeight_);
}
