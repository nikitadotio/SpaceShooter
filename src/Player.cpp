#include "Player.h"

Player::Player()
{
    health = 100.f;
    invincibilityTimer = 0.f;
    shape.setRadius(40.f);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(40.f, 40.f);
    position = {400.f, 410.f};
    speed = 200.f;
}

void Player::update(float dt)
{

    invincibilityTimer -= dt;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        position.x -= speed * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        position.x += speed * dt;

    
    shape.setPosition(position);   
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

void Player::takeDamage() {
    if (invincibilityTimer <= 0.f) {
        health *= 0.5f;
        invincibilityTimer = 1.0f;
    }
}

float Player::getHealth() {
    return health;
}
