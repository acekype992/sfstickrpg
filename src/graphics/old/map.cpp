#include "map.hpp"
#include <SFML/Graphics/Rect.hpp>

Map::Map(Tileset &tileset, const std::string &filename)
    : tileset_ {tileset}
{
    mapMatrix_.loadFromFile(filename);

    const size_type tw {tileset_.sizeOfTiles().x};
    const size_type th {tileset_.sizeOfTiles().y};

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(mapMatrix_.columns() * mapMatrix_.rows() * 4);

    for(std::size_t y {0}; y < mapMatrix_.rows(); ++y)
        for(std::size_t x {0}; x < mapMatrix_.columns(); ++x)
        {
            size_type tIndex = mapMatrix_(x,y);
            sf::IntRect tr = tileset_[tIndex];

            sf::Vertex *quad = &vertices_[(y * mapMatrix_.columns() + x) * 4];

            quad[0].position = sf::Vector2f(x * tw     , y * th);
            quad[1].position = sf::Vector2f((x+1) * tw , y * th);
            quad[2].position = sf::Vector2f((x+1) * tw , (y+1) * th);
            quad[3].position = sf::Vector2f(x * tw     , (y+1) * th);

            quad[0].texCoords = sf::Vector2f(tr.left * tw     , tr.top * th);
            quad[1].texCoords = sf::Vector2f((tr.left+1) * tw , tr.top * th);
            quad[2].texCoords = sf::Vector2f((tr.left+1) * tw , (tr.top+1) * th);
            quad[3].texCoords = sf::Vector2f(tr.left * tw     , (tr.top+1) * th);

//            sf::IntRect rect;
//            rect.left = x = tw;
//            rect.top  = y * tw;
//            rect.width  = tw;
//            rect.height = tw;
//            tilesRect_.push_back(rect);
        }
}


Map::Map(Tileset &tileset, size_type w, size_type h)
    : tileset_ {tileset}
{
    mapMatrix_.create(w, h);
    mapMatrix_.fill(1);

    const size_type tw {tileset_.sizeOfTiles().x};
    const size_type th {tileset_.sizeOfTiles().y};

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize((w * h) * 4);

    for(std::size_t y {0}; y < mapMatrix_.rows(); ++y)
        for(std::size_t x {0}; x < mapMatrix_.columns(); ++x)
        {
            size_type tIndex = mapMatrix_(x,y);
            sf::IntRect tr = tileset_[tIndex];

            sf::Vertex *quad = &vertices_[(y * mapMatrix_.rows() + x) * 4];

            quad[0].position = sf::Vector2f(x * tw     , y * th);
            quad[1].position = sf::Vector2f((x+1) * tw , y * th);
            quad[2].position = sf::Vector2f((x+1) * tw , (y+1) * th);
            quad[3].position = sf::Vector2f(x * tw     , (y+1) * th);

            quad[0].texCoords = sf::Vector2f(tr.left * tw     , tr.top * th);
            quad[1].texCoords = sf::Vector2f((tr.left+1) * tw , tr.top * th);
            quad[2].texCoords = sf::Vector2f((tr.left+1) * tw , (tr.top+1) * th);
            quad[3].texCoords = sf::Vector2f(tr.left * tw     , (tr.top+1) * th);

            sf::IntRect rect;
            rect.left = x * tw;
            rect.top  = y * tw;
            rect.width  = tw;
            rect.height = tw;
            tilesRect_.push_back(rect);
        }
}


void Map::setTile(size_type x, size_type y, sf::IntRect rect)
{
    const size_type tw {tileset_.sizeOfTiles().x};
    const size_type th {tileset_.sizeOfTiles().y};

    x /= tw;
    y /= th;

    sf::IntRect tr = rect;

    sf::Vertex *quad = &vertices_[(y * mapMatrix_.columns() + x) * 4];

    quad[0].texCoords = sf::Vector2f(tr.left * tw     , tr.top * th);
    quad[1].texCoords = sf::Vector2f((tr.left+1) * tw , tr.top * th);
    quad[2].texCoords = sf::Vector2f((tr.left+1) * tw , (tr.top+1) * th);
    quad[3].texCoords = sf::Vector2f(tr.left * tw     , (tr.top+1) * th);
}


sf::FloatRect Map::getBoundingRect() const noexcept
{
    return sf::FloatRect(sf::Transformable::getPosition().x,
                         sf::Transformable::getPosition().y,
                         getSize().x,
                         getSize().y);
}


sf::Vector2u Map::getSize() const noexcept
{
    return sf::Vector2u(mapMatrix_.columns() * tileset_.sizeOfTiles().x,
                        mapMatrix_.rows()    * tileset_.sizeOfTiles().y);
}


void Map::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileset_.getTexture();
    target.draw(vertices_, states);
}
