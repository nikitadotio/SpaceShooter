#pragma once
#include "Entity.h"

class Asteroid : public Entity {
public:
    Asteroid();
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    bool escaped = false;

private:
    static sf::Texture texture;
    static bool textureLoaded;
    sf::Sprite sprite;
    float angle;
    float rotSpeed;
};