#include <SFML/Graphics.hpp>
#include <cmath>
#include "Player.h"
#include "Asteroid.h"

int main()
  {

      sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");
      Player player;                                                                                       
      std::vector<Asteroid> asteroids{Asteroid(), Asteroid(), Asteroid(), Asteroid(), Asteroid(), Asteroid(), Asteroid(), Asteroid(), Asteroid()};
      sf::Clock clock;
      float shakeTimer = 0.f;
      sf::View view = window.getDefaultView();
      std::vector<sf::RectangleShape> stars(40);
      std::vector<float> starSpeeds(40);
          for (int i{}; i <40; ++i) {
              float x = std::rand() % 800;
              float y = std::rand() % 600;
              stars[i].setSize({1.f, 15.f});
              stars[i].setPosition(x, y);
              stars[i].setFillColor (sf::Color(255, 255, 255, 60));
              starSpeeds[i] = std::rand() % 150;
    }

          while(window.isOpen()){
              float dt = clock.restart().asSeconds();
      sf::Event event;
          while (window.pollEvent(event))
          {                                                                                                
              if(event.type == sf::Event::Closed)
                  window.close();                                                                          
          }                                                 

          player.update(dt);
          for (auto& a : asteroids) a.update(dt);
          for (auto& a : asteroids) {
              float dx = player.position.x - a.position.x;
              float dy = player.position.y - a.position.y;
              if (std::hypot(dx, dy) < 60.f) {
                  player.takeDamage();
                  shakeTimer = 0.3f;   // Trigger Shake
              }
          }

          if (shakeTimer > 0.f) {
              shakeTimer -= dt;
              float offSetX = (std::rand() % 10 - 5);
              float offSetY = (std::rand() % 10 - 5);
              view.setCenter(400.f + offSetX, 300.f + offSetY);
          }
          else {
              view.setCenter(400.f, 300.f);

          }
          window.setView(view);
              for (int i = 0; i < 40; ++i ) {
                  stars[i].move(0, starSpeeds[i] * dt);
                  if (stars[i].getPosition().y > 600.f) stars[i].setPosition(std::rand() % 800, 0.f);
              }
          window.clear();
          for (auto& s : stars) window.draw(s);

          player.draw(window);
          for (auto& a : asteroids) a.draw(window);
          window.display();                                                                                
      }
                                                                                                           
      return 0;                                             
  }


