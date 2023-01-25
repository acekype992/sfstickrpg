#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>

#include "tileset.hpp"

class Map : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
{
    using size_type = std::size_t;

public:
    Map()
    {}

    void initialize(size_type width, size_type height, const Tileset &tileset)
    {
        tileset_ = &tileset;

        vertices_.setPrimitiveType(sf::Quads);
        vertices_.resize(width * height * 4);

        tileSize_ = tileset_->getTileSize();

        mapSize_.x = (width * tileset_->getTileSize().x) - tileset_->getTileSize().x;
        mapSize_.y = (height * tileset_->getTileSize().y) - tileset_->getTileSize().y;

        width = tileset_->getTexture().getSize().x / tileSize_.x;
        height = tileset_->getTexture().getSize().y / tileSize_.y;

        for(std::size_t y {0}; y < height; ++y)
        {
            for(std::size_t x {0}; x < width; ++x)
            {
                sf::Vertex *quad = &vertices_[(y * width + x) * 4];

                auto r = (*tileset_)(x,y);

                quad[0].position = sf::Vector2f(x * tileSize_.x     , y * tileSize_.y);
                quad[1].position = sf::Vector2f((x+1) * tileSize_.x , y * tileSize_.y);
                quad[2].position = sf::Vector2f((x+1) * tileSize_.x , (y+1) * tileSize_.y);
                quad[3].position = sf::Vector2f(x * tileSize_.x     , (y+1) * tileSize_.y);

                quad[0].texCoords = sf::Vector2f(r.left * tileSize_.x     , r.top * tileSize_.y);
                quad[1].texCoords = sf::Vector2f((r.left+1) * tileSize_.x , r.top * tileSize_.y);
                quad[2].texCoords = sf::Vector2f((r.left+1) * tileSize_.x , (r.top+1) * tileSize_.y);
                quad[3].texCoords = sf::Vector2f(r.left * tileSize_.x     , (r.top+1) * tileSize_.y);
            }
        }
    }


protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &tileset_->getTexture();
        target.draw(vertices_, states);
    }


private:
    const Tileset *tileset_;
    sf::VertexArray vertices_;
    sf::Vector2u mapSize_;
    sf::Vector2u tileSize_;
};


#endif // MAP_HPP
