#include <iostream>
#include <conio.h>
#include "game.cpp"

int main(){
    char c;
    Map::State state = Map::Action;
    Map* map = new Map(4);
    Game game(map);
    while ( state ){
          game.play(state);
          c = getch();
          game.movement(c, state);
    }
    game.end();
    return 0;
}
