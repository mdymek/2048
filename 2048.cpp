#include <iostream>
#include <conio.h>
#include "map.cpp"
using namespace std;

bool game = true;

int main(){
    char c;
    while ( game ){
        draw();
        c = getch();
        movement(c);
        if ( placesLeft == 0 ) game = false;
    }
    end();
    return 0;
}


/*
- znaleźć bugi
- brak wykonania ruchu = brak randomu (enum flag)
- score
- ładniejszy wygląd
*/
