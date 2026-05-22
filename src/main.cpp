#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "Player.h"
#include "Asteroid.h"

// Returns a centred button shape + label pair
static sf::RectangleShape makeButton(float cx, float cy, float w, float h)
{
    sf::RectangleShape btn({w, h});
    btn.setOrigin(w / 2.f, h / 2.f);
    btn.setPosition(cx, cy);
    btn.setFillColor(sf::Color(60, 60, 60));
    btn.setOutlineColor(sf::Color::White);
    btn.setOutlineThickness(2.f);
    return btn;
}

static bool buttonClicked(const sf::RectangleShape& btn, sf::Vector2i mousePos)
{
    return btn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
    window.setFramerateLimit(60);

    auto makeAsteroids = []() {
        return std::vector<Asteroid>(9);
    };

    Player player;
    std::vector<Asteroid> asteroids = makeAsteroids();
    sf::Clock clock;
    float shakeTimer = 0.f;
    sf::View gameView = window.getDefaultView();

    std::vector<sf::RectangleShape> stars(40);
    std::vector<float> starSpeeds(40);
    for (int i{}; i < 40; ++i) {
        stars[i].setSize({1.f, 15.f});
        stars[i].setPosition(std::rand() % 800, std::rand() % 600);
        stars[i].setFillColor(sf::Color(255, 255, 255, 60));
        starSpeeds[i] = 50.f + std::rand() % 100;
    }

    sf::Font font;
    font.loadFromFile("assets/fonts/DejaVuSans.ttf");

    // HUD
    sf::Text scoreText, livesText;
    for (auto* t : {&scoreText, &livesText}) {
        t->setFont(font);
        t->setCharacterSize(24);
        t->setFillColor(sf::Color::White);
    }
    scoreText.setPosition(10.f, 10.f);
    livesText.setPosition(10.f, 40.f);

    // Game over screen
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(54);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER");

    sf::Text finalScoreText;
    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::White);

    // Buttons
    auto restartBtn = makeButton(400.f, 390.f, 180.f, 50.f);
    auto exitBtn    = makeButton(400.f, 460.f, 180.f, 50.f);

    sf::Text restartLabel, exitLabel;
    for (auto* t : {&restartLabel, &exitLabel}) {
        t->setFont(font);
        t->setCharacterSize(22);
        t->setFillColor(sf::Color::White);
    }
    restartLabel.setString("Restart");
    exitLabel.setString("Exit");

    auto centreLabel = [](sf::Text& label, const sf::RectangleShape& btn) {
        sf::FloatRect b = label.getLocalBounds();
        sf::Vector2f c = btn.getPosition();
        label.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
        label.setPosition(c);
    };
    centreLabel(restartLabel, restartBtn);
    centreLabel(exitLabel, exitBtn);

    int score = 0;
    int escapedCount = 0;
    bool gameOver = false;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameOver && event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mp = {event.mouseButton.x, event.mouseButton.y};
                if (buttonClicked(restartBtn, mp)) {
                    player    = Player();
                    asteroids = makeAsteroids();
                    score = escapedCount = 0;
                    gameOver   = false;
                    shakeTimer = 0.f;
                    gameView   = window.getDefaultView();
                } else if (buttonClicked(exitBtn, mp)) {
                    window.close();
                }
            }
        }

        if (!gameOver) {
            player.update(dt);

            for (auto& a : asteroids) {
                a.update(dt);
                if (a.escaped) {
                    ++escapedCount;
                    if (escapedCount % 5 == 0)
                        score += 5;
                }
            }

            for (auto& a : asteroids) {
                float dx = player.position.x - a.position.x;
                float dy = player.position.y - a.position.y;
                if (std::hypot(dx, dy) < 60.f) {
                    player.takeDamage();
                    shakeTimer = 0.3f;
                }
            }

            if (player.getLives() <= 0)
                gameOver = true;

            if (shakeTimer > 0.f) {
                shakeTimer -= dt;
                gameView.setCenter(400.f + (std::rand() % 10 - 5),
                                   300.f + (std::rand() % 10 - 5));
            } else {
                gameView.setCenter(400.f, 300.f);
            }
            window.setView(gameView);

            for (int i = 0; i < 40; ++i) {
                stars[i].move(0, starSpeeds[i] * dt);
                if (stars[i].getPosition().y > 600.f)
                    stars[i].setPosition(std::rand() % 800, 0.f);
            }
        }

        // Update HUD text
        scoreText.setString("Score: " + std::to_string(score));
        std::string livesStr = "Lives: ";
        for (int i = 0; i < player.getLives(); ++i) livesStr += "* ";
        livesText.setString(livesStr);

        window.clear();
        for (auto& s : stars) window.draw(s);

        if (!gameOver) {
            player.draw(window);
            for (auto& a : asteroids) a.draw(window);
            window.setView(window.getDefaultView());
            window.draw(scoreText);
            window.draw(livesText);
        } else {
            window.setView(window.getDefaultView());

            sf::FloatRect goBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(goBounds.left + goBounds.width / 2.f,
                                   goBounds.top  + goBounds.height / 2.f);
            gameOverText.setPosition(400.f, 200.f);

            finalScoreText.setString("Final Score: " + std::to_string(score));
            sf::FloatRect fsBounds = finalScoreText.getLocalBounds();
            finalScoreText.setOrigin(fsBounds.left + fsBounds.width / 2.f,
                                     fsBounds.top  + fsBounds.height / 2.f);
            finalScoreText.setPosition(400.f, 300.f);

            window.draw(gameOverText);
            window.draw(finalScoreText);
            window.draw(restartBtn);
            window.draw(exitBtn);
            window.draw(restartLabel);
            window.draw(exitLabel);
        }

        window.display();
    }

    return 0;
}