#include "map.hpp"

Map::Map( int S ) {
    for ( int i = 0; i < S; i++ ){
        std::vector<Cell> row;
        for ( int j = 0; j < S; j++ ){
            Cell c;
            row.push_back(c);
        }
        map.push_back(row);
    }
    size = S;
    score = 0;
    placesLeft = S*S;
}

Map::~Map(){}

void Map::random() {
    int x = rand() % 4;
    int y = rand() % 4;
    while ( map[x][y].value() != 0 ){
        x = rand() % 4;
        y = rand() % 4;
    }

    int c = rand() % 3;
    if ( c < 2 ) map[x][y].setVal(2);
    else map[x][y].setVal(4);
    placesLeft--;
}

void Map::draw(State& state) {
    system("cls");
    if ( state == Action ) random();
    for ( int y = 0; y < size; y++ ){
        for (int x = 0; x <= size; x++){
            if ( x == size) std::cout << "|";
            else{
                map[x][y].unchange();
                if ( map[x][y].value() == 0 ) std::cout << "|    ";
                else {
                    std::cout << "|" << " " << map[x][y].value();
                    if ( map[x][y].value() < 10 ) std::cout << "  ";
                    else if ( map[x][y].value() < 100 ) std::cout << " ";
                }
            }
        }
        std::cout << std::endl << " ";
        for ( int x = 0; x < size; x++ ) std::cout << "-----";
        std::cout << std::endl;
    }
    std::cout << "score: " << score << std::endl;
}

int Map::checkY(int x, int y, int sY, int val){
    int newY = y-sY;
    if ( (newY >= 0 && newY < size) && map[x][newY].value() == 0 ) newY = checkY(x, newY, sY, val);

    if ( newY >= 0 && newY < size && ((map[x][newY].value() == val && map[x][newY].unchanged()) || map[x][newY].value() == 0)) return newY;
    else return newY+sY;
}

int Map::checkX(int x, int y, int sX, int val){
    int newX = x-sX;
    if ( (newX >= 0 && newX < size) && map[newX][y].value() == 0 ) newX = checkX(newX, y, sX, val);

    if ( newX >= 0 && newX < size && ((map[newX][y].value() == val && map[newX][y].unchanged()) || map[newX][y].value() == 0)) return newX;
    else return newX+sX;
}

void Map::move(int sX, int sY, State& state){
    int toScore = 0;
    if ( sX == 0 ){
        for ( int x = 0; x < size; x++ ){
            for ( int y = (size + sY)%size; y >= 0 && y < size; y += sY ){
                if ( map[x][y].value() != 0 ){
                    int newY = checkY(x, y, sY, map[x][y].value());
                    if ( y != newY){
                        if ( map[x][newY].value() != 0 ) {
                            placesLeft++;
                            toScore = 2*map[x][newY].value();
                            map[x][newY].change();
                        }
                        map[x][newY].setVal(map[x][newY].value() + map[x][y].value());
                        map[x][y].setVal(0);
                        state = Map::Action;
                    }
                }
            }
        }
    }
    else {
        for ( int y = 0; y < size; y++ ){
            for ( int x = (size + sX)%size; x >= 0 && x < size; x += sX ){
                if ( map[x][y].value() != 0 ){
                    int newX = checkX(x, y, sX, map[x][y].value());
                    if ( x != newX){
                        if ( map[newX][y].value() != 0 ) {
                            placesLeft++;
                            toScore = 2*map[newX][y].value();
                            map[newX][y].change();
                        }
                        map[newX][y].setVal(map[newX][y].value() + map[x][y].value());
                        map[x][y].setVal(0);
                        state = Map::Action;
                    }
                }
            }
        }
    }
    if ( placesLeft == 0 ) state = End;
    if ( toScore == 2048 ) state = Score;
    score += toScore;
}
