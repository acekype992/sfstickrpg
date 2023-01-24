#ifndef PLAYER_ENTITY_HPP
#define PLAYER_ENTITY_HPP

#include "entity.hpp"


class PlayerEntity : public Entity
{
public:

    bool animate_;

    PlayerEntity();

    virtual ~PlayerEntity() = default;

    virtual void update() override;

    void setTileset(sf::Vector2i tileSize, sf::Texture &texture, int anims, bool direction);
    void setDirection(Direction direction);
    void move(float x, float y);
    void cancelMove();
    sf::FloatRect getBoundingRect()
    {
        return getTransform().transformRect(sprite_.getLocalBounds());
    }

private:
    sf::Clock clockAnim_;

    int animation_count_;
    int current_animation_;
    Direction direction_;
    int current_direction_;

    sf::Vector2f lastPos_;

    sf::Vector2i tileSize_;
};

#endif // PLAYER_ENTITY_HPP
