#include <iostream>
#include <conio.h>
//#include "game.hpp"
#include "map.cpp"

int main(){
    char c;
    Map::State state = Map::Action;
    Map map(4);
    while ( state ){
        map.draw(state);
        c = getch();
        map.movement(c, state);
    }
    map.end();
    return 0;
}
