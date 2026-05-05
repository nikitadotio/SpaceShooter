#pragma once
#include "Entity.h"
 
class Player : public Entity
{
    public:
        Player();
        void takeDamage();
        float getHealth();
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;

    private:
        sf::CircleShape shape;
        float speed;
        float health;
        float invincibilityTimer;
};

