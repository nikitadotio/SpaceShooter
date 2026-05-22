#include "Asteroid.h"
#include <random>

static std::mt19937 rng(std::random_device{}());
static std::uniform_real_distribution<float> xDist(20.f, 740.f);
static std::uniform_real_distribution<float> yDist(-500.f, -64.f);
static std::uniform_real_distribution<float> speedDist(180.f, 320.f);
static std::uniform_real_distribution<float> rotDist(-120.f, 120.f);
static std::uniform_real_distribution<float> scaleDist(0.7f, 1.4f);

sf::Texture Asteroid::texture;
bool Asteroid::textureLoaded = false;

Asteroid::Asteroid()
{
    if (!textureLoaded) {
        texture.loadFromFile("../assets/textures/asteroid.png");
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(32.f, 32.f);

    float s = scaleDist(rng);
    sprite.setScale(s, s);

    angle    = 0.f;
    rotSpeed = rotDist(rng);
    velocity = {0.f, speedDist(rng)};
    position = {xDist(rng), yDist(rng)};
}

void Asteroid::update(float dt)
{
    position += velocity * dt;
    angle    += rotSpeed * dt;
    escaped   = false;

    if (position.y > 660.f) {
        escaped  = true;
        position = {xDist(rng), yDist(rng)};
        velocity = {0.f, speedDist(rng)};
        float s  = scaleDist(rng);
        sprite.setScale(s, s);
    }
}

void Asteroid::draw(sf::RenderWindow& window)
{
    sprite.setPosition(position);
    sprite.setRotation(angle);
    window.draw(sprite);
}