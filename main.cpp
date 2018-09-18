#include <conio.h>
#include "game.cpp"

int main(){
    int noMove = 0;
    bool wait = false;
    Map::State state = Map::Action;
    Map* map = new Map(4);
    Game game(map);

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
                if ( state == Map::End ){
                    window.close();
                }
                else if ( state == Map::Score ){
                    if (event.key.code == sf::Keyboard::Y){
                        state = Map::Action;
                    }
                    else {
                        state = Map::End;
                    }
                }
                else {
                    if (event.key.code == sf::Keyboard::Escape){
                        window.close();
                    }
                    else {
                        game.movement(event.key.code, state, noMove);
                    }
                }
            }
        }
    }
    return 0;
}
