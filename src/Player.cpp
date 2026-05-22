#include "Player.h"

sf::Texture Player::texture;
bool Player::textureLoaded = false;

Player::Player()
{
    if (!textureLoaded) {
        texture.loadFromFile("assets/textures/ship.png");
        textureLoaded = true;
    }
    sprite.setTexture(texture);
    // origin at centre of the 64x80 sprite
    sprite.setOrigin(32.f, 40.f);

    lives = 3;
    invincibilityTimer = 0.f;
    speed = 200.f;
    position = {400.f, 500.f};
}

void Player::update(float dt)
{
    invincibilityTimer -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        position.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        position.x += speed * dt;

    // clamp to screen
    position.x = std::max(32.f, std::min(768.f, position.x));

    sprite.setPosition(position);

    // flash during invincibility
    sf::Uint8 alpha = (invincibilityTimer > 0.f && static_cast<int>(invincibilityTimer * 8) % 2 == 0)
                      ? 100 : 255;
    sprite.setColor(sf::Color(255, 255, 255, alpha));
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Player::takeDamage()
{
    if (invincibilityTimer <= 0.f) {
        --lives;
        invincibilityTimer = 1.5f;
    }
}

int Player::getLives()
{
    return lives;
}