#include "player_entity.hpp"


PlayerEntity::PlayerEntity()
    : direction_{Direction::down}
    , current_animation_ {0}
    , current_direction_ {0}
{}



void PlayerEntity::setTileset(sf::Vector2i tileSize, sf::Texture &texture, int anims, bool direction)
{
    setTexture(texture);
    tileSize_ = tileSize;
    animation_count_ = anims;
}


void PlayerEntity::update()
{
    switch(direction_)
    {
    case Direction::up:
        current_direction_ = 1;
        break;
    case Direction::left:
        current_direction_ = 2;
        break;
    case Direction::right:
        current_direction_ = 3;
        break;
    case Direction::down:
        current_direction_ = 0;
        break;
    }

    if(clockAnim_.getElapsedTime().asSeconds() > 0.25)
    {
        if(animate_)
        {
            ++current_animation_;
            if(current_animation_ > (animation_count_ - 1))
            {
                current_animation_ = 0;
            }
        }
        else
        {
            current_animation_ = 0;
        }
        clockAnim_.restart();
    }

    sf::IntRect rect {current_animation_ * tileSize_.x,
                      current_direction_ * tileSize_.y,
                      tileSize_.x,
                      tileSize_.y
                     };

    sprite_.setTextureRect(rect);
}


void PlayerEntity::setDirection(Direction direction)
{
    direction_ = direction;
}


void PlayerEntity::move(float x, float y)
{
    lastPos_ = sf::Transformable::getPosition();
    sf::Transformable::move(x, y);
}


void PlayerEntity::cancelMove()
{
    sf::Transformable::setPosition(lastPos_);
}
