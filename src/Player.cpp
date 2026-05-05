#include "Player.h"

Player::Player()
{
    shape.setRadius(40.f);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(40.f, 40.f);
    position = {400.f, 410.f};
    speed = 200.f;
}

void Player::update(float dt)
{

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
