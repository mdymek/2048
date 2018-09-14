#include <iostream>
#include <conio.h>
#include "map.cpp"

bool game = true;

int main(){
    char c;
    Map map(4);
    while ( game ){
        map.draw();
        c = getch();
        map.movement(c);
        if ( map.getPlacesLeft() == 0 ) game = false;
    }
    map.end();
    return 0;
}


/*
enum state
*/
