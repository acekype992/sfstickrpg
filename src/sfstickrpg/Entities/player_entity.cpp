#include "player_entity.hpp"


PlayerEntity::PlayerEntity()
    : direction {Direction::down}
    , animOn {false}
    , animCount_ {1}
    , animMove_ {0}
    , animDir_ {0}
{
}


void PlayerEntity::update()
{
    switch(direction)
    {
    case Direction::up:
        animDir_ = 1;
        break;
    case Direction::left:
        animDir_ = 2;
        break;
    case Direction::right:
        animDir_ = 3;
        break;
    case Direction::down:
        animDir_ = 0;
        break;

    default:
        break;
    }

    if(animClock_.getElapsedTime().asSeconds() > 0.25)
    {
        if(animOn)
        {
            ++animMove_;
            if(animMove_ > (animCount_ - 1))
                animMove_ = 0;
        }
        else if(animMove_ > 0)
        {
            animMove_ = 0;
        }
        animClock_.restart();
    }

    sf::IntRect rect = (*tileset_)(animMove_, animDir_);
    rect.left *= tileset_->getTileSize().x;
    rect.top  *= tileset_->getTileSize().y;

    sprite_.setTextureRect(rect);
}


