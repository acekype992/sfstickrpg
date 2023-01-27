#ifndef PLAYER_ENTITY_HPP
#define PLAYER_ENTITY_HPP

#include <SFML/System/Clock.hpp>

#include "entity.hpp"


class PlayerEntity : public Entity
{
public:
    PlayerEntity();

    virtual ~PlayerEntity() = default;

    virtual void update() override;

    void setAnim(int anims)
    {
        animCount_ = anims;
    }

    bool animOn;
    Direction direction;
    float speed;
private:
    sf::Clock animClock_;
    int  animCount_;
    int  animMove_;
    int  animDir_;

};

#endif // PLAYER_ENTITY_HPP
