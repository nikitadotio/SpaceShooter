#pragma once
#include "Entity.h"

class Asteroid : public Entity {
public:
    Asteroid();
    void update(float dt)override;
    void draw(sf::RenderWindow& window)override;


private:
    sf::CircleShape shape;
    float angle;
};