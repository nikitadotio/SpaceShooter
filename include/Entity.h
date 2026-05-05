#pragma once 
#include <SFML/Graphics.hpp>

class Entity
{
    public:
    sf::Vector2f position;
    sf::Vector2f velocity;

    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual ~Entity() = default;
};

