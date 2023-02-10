#include "tileset.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#define sf_IS_KEY_PRESSED(...) sf::Keyboard::isKeyPressed(__VA_ARGS__)

Tileset::Tileset(sf::Vector2u tileSize, const std::string &filename)
    : drawEnable_ {false}
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

#include <SFML/Window/Event.hpp>
#include <iostream>
void Tileset::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(drawEnable_)
    {
        states.transform *= getTransform();
        states.texture = texture_.get();

        target.draw(vertices_, states);
        target.draw(selectCase_, states);
    }

    if(drawCurrentCase_)
    {
        target.draw(currentCase_, states);
    }
}


void Tileset::keyPressEvent(const sf::Event::KeyEvent &event)
{
    if(keyControlPressed() && keyMajPressed() &&
       sf_IS_KEY_PRESSED(sf::Keyboard::T))
    {
        drawEnable_ ? drawEnable_ = false : drawEnable_ = true;
    }
}


void Tileset::mouseClickEvent(const sf::Event::MouseButtonEvent &event, const sf::RenderWindow &window)
{
    if(drawEnable_ && drawCurrentCase_)
    {
        sf::Vector2i p {event.x, event.y};
        p.x = event.x / 32;
        p.y = event.y / 32;

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y));
        int px = mousePos.x / 32;
        int py = mousePos.y / 32;


        const auto& r = (*this)(px, py);
        selectCase_.setPosition(r.left * 32, r.top * 32);
    }
}


void Tileset::mouseMoveEvent(sf::Event::MouseMoveEvent &event, const sf::RenderWindow &window)
{
    if(drawEnable_)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.x, event.y));
        int px = mousePos.x;
        int py = mousePos.y;

        if(getGlobalBounds().contains(px, py))
        {
            px /= 32;
            py /= 32;

            const auto& r = (*this)(px, py);
            currentCase_.setPosition(r.left * 32, r.top * 32);
            drawCurrentCase_ = true;
        }
        else
        {
            drawCurrentCase_ = false;
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

