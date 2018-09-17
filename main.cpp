#include <iostream>
#include <conio.h>
#include "game.cpp"

int main(){
    char c;
    Map::State state = Map::Action;
    Map* map = new Map(4);
    Game game(map);

    sf::CircleShape cr(200);
    sf::RenderWindow window(sf::VideoMode(420,420), "win");

    while ( window.isOpen() ){
          window.clear();
          game.play(state, window);
          //c = getch();
          //game.movement(c, state);
          sf::Event event;
          while ( window.pollEvent(event) ){
              if ( event.type == sf::Event::Closed){
                  window.close();
              }
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                game.movement('a', state);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                game.movement('d', state);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                game.movement('w', state);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                game.movement('s', state);
          }
          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
          {
                window.close();
          }

          window.display();
    }
    game.end();

    return 0;
}
