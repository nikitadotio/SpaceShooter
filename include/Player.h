#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player();
    void takeDamage();
    int getLives();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;

private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;
    float speed;
    int lives;
    float invincibilityTimer;
};