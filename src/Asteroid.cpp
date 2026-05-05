#include <SFML/Graphics.hpp>
#include "Asteroid.h"
#include <random>

static std::mt19937 rng(std::random_device{}());
static std::uniform_real_distribution<float> xDist(20.f, 760.f);
static std::uniform_real_distribution<float> yDist(-400.f, 0.f); //staggered

Asteroid::Asteroid() {
    shape.setFillColor(sf::Color::White);
    shape.setRadius(20.f);
    shape.setOrigin(20.f, 20.f);
    velocity = {0.f, 275.f};
    position = {xDist(rng), yDist(rng)};

}


    void Asteroid::update(float dt) {
    position += velocity * dt;

    if (position.y > 620.f) {
        position = {xDist(rng), yDist(rng)};
    }
}
    void Asteroid::draw(sf::RenderWindow& window){
        shape.setPosition(position);
        window.draw(shape);
    }


