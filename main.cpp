
#include <conio.h>
#include "game.cpp"

int main(){
    char c;
    bool wait = false;
    Map::State state = Map::Action;
    Map* map = new Map(4);
    Game game(map);

    sf::CircleShape cr(200);
    sf::RenderWindow window(sf::VideoMode(400,400), "2048");

    while ( window.isOpen() ){
        if ( !wait ){
            window.clear();
            game.play(state, window);
            window.display();
            wait = true;
        }
        sf::Event event;
        while ( window.pollEvent(event) ){
            if ( event.type == sf::Event::Closed){
                window.close();
            }
            else if ( event.type == sf::Event::KeyPressed ){
                wait = false;
                if (event.key.code == sf::Keyboard::Escape){
                    window.close();
                }
                else {
                    game.movement(event.key.code, state);
                }
            }
        }
    }
    game.end();
    return 0;
}
