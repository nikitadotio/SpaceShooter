#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
  {
      sf::RenderWindow window(sf::VideoMode(800, 600), "My First Game");                                   
   
      Player player;                                                                                       
                                                            
      sf::Clock clock;                                                                                     
   
      while(window.isOpen()){                                                                              
          float dt = clock.restart().asSeconds();           

          sf::Event event;
          while (window.pollEvent(event))
          {                                                                                                
              if(event.type == sf::Event::Closed)
                  window.close();                                                                          
          }                                                 

          player.update(dt);

          window.clear();
          player.draw(window);
          window.display();                                                                                
      }
                                                                                                           
      return 0;                                             
  }


