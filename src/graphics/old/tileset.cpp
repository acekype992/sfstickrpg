#include "tileset.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>


#define sf_IS_KEY_PRESSED(...) sf::Keyboard::isKeyPressed(__VA_ARGS__)


Tileset::Tileset(sf::Vector2u tileSize, const std::string &filename)
    :  eventHandle_ {*this}
    ,  drawEnable_ {false}
    , drawCurrentCase_ {false}
{
    texture_ = std::make_unique<sf::Texture>();
    if(!texture_->loadFromFile(filename))
        throw std::runtime_error("Cannot open file for tileset");

    tilesetSize_ = texture_->getSize();
    tileSize_ = tileSize;

    sf::Vector2u matrixSize { tilesetSize_.x / tileSize_.x, tilesetSize_.y / tileSize_.y};
    tilesMatrix_.create(matrixSize.x, matrixSize.y);

    vertices_.setPrimitiveType(sf::Quads);
    vertices_.resize(matrixSize.x * matrixSize.y * 4);

    for(std::size_t y {0}; y < matrixSize.y; ++y)
        for(std::size_t x {0}; x < matrixSize.x; ++x)
        {
            sf::IntRect &tr = tilesMatrix_(x,y);
                tr.left   = x;
                tr.top    = y;
                tr.width  = tileSize_.x;
                tr.height = tileSize_.y;

            sf::Vertex *quad = &vertices_[(y * matrixSize.x + x) * 4];

            quad[0] = sf::Vector2f(x * tr.width     , y * tr.height);
            quad[1] = sf::Vector2f((x+1) * tr.width , y * tr.height);
            quad[2] = sf::Vector2f((x+1) * tr.width , (y+1) * tr.height);
            quad[3] = sf::Vector2f(x * tr.width     , (y+1) * tr.height);

            quad[0].texCoords = sf::Vector2f(tr.left * tr.width     , tr.top * tr.height);
            quad[1].texCoords = sf::Vector2f((tr.left+1) * tr.width , tr.top * tr.height);
            quad[2].texCoords = sf::Vector2f((tr.left+1) * tr.width , (tr.top+1) * tr.height);
            quad[3].texCoords = sf::Vector2f(tr.left * tr.width     , (tr.top+1) * tr.height);

            tiles_.insert({tiles_.size(), tr});
        }

    currentCase_.setSize(sf::Vector2f(tileSize_));
    currentCase_.setFillColor(sf::Color(255, 255, 255, 120));

    selectCase_.setSize(sf::Vector2f(tileSize_.x, tileSize.y));
    selectCase_.setFillColor(sf::Color(255, 255, 255, 180));
}


sf::Texture& Tileset::getTexture() const noexcept
{
    return *texture_.get();
}


sf::Vector2u Tileset::sizeOfTileset() const noexcept
{
    return tilesetSize_;
}


sf::Vector2u Tileset::sizeOfTiles() const noexcept
{
    return tileSize_;
}


sf::IntRect Tileset::operator()(size_type x, size_type y) const noexcept
{
    return tilesMatrix_(x, y);
}


sf::IntRect Tileset::operator[](size_type i) const  noexcept
{
    return tiles_.find(i)->second;
}


void Tileset::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(drawEnable_)
    {
        states.transform *= getTransform();
        states.texture = texture_.get();

        target.draw(vertices_, states);
        target.draw(selectCase_, states);
        if(drawCurrentCase_)
        {
            target.draw(currentCase_, states);
        }
    }

}


sf::IntRect Tileset::getGlobalBounds() const noexcept
{
    sf::IntRect rect;
    rect.width = texture_->getSize().x;
    rect.height = texture_->getSize().y;
    rect.left = sf::Transformable::getPosition().x;
    rect.top = sf::Transformable::getPosition().y;

    return rect;
}


bool Tileset::keyControlPressed()
{
    if(sf_IS_KEY_PRESSED(sf::Keyboard::LControl) ||
       sf_IS_KEY_PRESSED(sf::Keyboard::RControl))
        return 1;

    return 0;
}


bool Tileset::keyMajPressed()
{
    if(sf_IS_KEY_PRESSED(sf::Keyboard::LShift) ||
       sf_IS_KEY_PRESSED(sf::Keyboard::RShift))
        return 1;

    return 0;
}

