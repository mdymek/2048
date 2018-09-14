#include "map.hpp"

Map::Map( int S ) {
    for ( int i = 0; i < S; i++ ){
        std::vector<int> row;
        for ( int j = 0; j < S; j++ ) row.push_back(0);
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
    while ( map[x][y] != 0 ){
        x = rand() % 4;
        y = rand() % 4;
    }

    int c = rand() % 2;
    if ( c == 0 ) map[x][y] = 2;
    else map[x][y] = 4;
    placesLeft--;
}

void Map::draw(State& state) {
    system("cls");
    if ( state == Action ) random();
    for ( int y = 0; y < size; y++ ){
        for (int x = 0; x <= size; x++){
            if ( x == size) std::cout << "|";
            else if ( map[x][y] == 0 ) std::cout << "|    ";
            else {
                std::cout << "|" << " " << map[x][y];
                if ( map[x][y] < 10 ) std::cout << "  ";
                else if ( map[x][y] < 100 ) std::cout << " ";
            }
        }
        std::cout << std::endl << " ";
        for ( int x = 0; x < size; x++ ) std::cout << "-----";
        std::cout << std::endl;
    }
    std::cout << "score: " << score << std::endl;
    if ( state == Score ){
        std::cout << std::endl << "Congratulations! You made 2048." << std::endl << "Do you want to contiune playing? Y/N" << std::endl;
        char c;
        std::cin >> c;
        if ( c == 'Y' ) state = Action;
        else state = End;
    }
}

void Map::end() const {
    std::cout << std::endl << "You lose! Your score is " << score << "." << std::endl;
    std::fstream file;
    file.open("score.txt");
    int highscore;
    file >> highscore;
    if (score > highscore) {
        std::cout << "You beat your highscore!" << std::endl;

        file.close();
        file.open("score.txt", std::ofstream::trunc);
        file.close();
        file.open("score.txt");
        file << score;
        file.close();
    }
    else {
        std::cout << "Your current highscore is " << highscore << "." << std::endl;
        file.close();
    }
}

int Map::getScore() const { return score; }
int Map::getPlacesLeft() const { return placesLeft; }
void Map::setPlacesLeft( int p ) { placesLeft = p; }

int Map::checkW(int x, int y, int val){
    int newY = y-1;
    if ( map[x][newY] == 0 && newY > 0) newY = checkW(x, newY, val);

    if (map[x][newY] == val || map[x][newY] == 0) return newY;
    else return newY+1;
}

int Map::checkS(int x, int y, int val){
    int newY = y+1;
    if ( map[x][newY] == 0 && newY < size-1) newY = checkS(x, newY, val);

    if (map[x][newY] == val || map[x][newY] == 0) return newY;
    else return newY-1;
}

int Map::checkA(int x, int y, int val){
    int newX = x-1;
    if ( map[newX][y] == 0 && newX > 0) newX = checkA(newX, y, val);

    if (map[newX][y] == val || map[newX][y] == 0) return newX;
    else return newX+1;
}

int Map::checkD(int x, int y, int val){
    int newX = x+1;
    if ( map[newX][y] == 0 && newX < size-1) newX = checkD(newX, y, val);

    if (map[newX][y] == val || map[newX][y] == 0) return newX;
    else return newX-1;
}

void Map::movement(char c, State& state){
    int toScore = 0;
    state = Pass;
    switch(c){
        case 'w':
            for ( int y = 1; y < size; y++ ){
                for ( int x = 0; x < size; x++ ){
                    if ( map[x][y] != 0 ){
                        int newY = checkW(x,y,map[x][y]);
                        if ( y != newY){
                            if ( map[x][newY] != 0 ) {
                                placesLeft++;
                                toScore = 2*map[x][newY];
                            }
                            map[x][newY] += map[x][y];
                            map[x][y] = 0;
                            state = Action;
                        }
                    }
                }
            }
            break;
        case 's':
            for ( int y = size-2; y >= 0; y-- ){
                for ( int x = 0; x < size; x++ ){
                    if ( map[x][y] != 0 ){
                        int newY = checkS(x,y,map[x][y]);
                        if ( y != newY){
                            if ( map[x][newY] != 0 ) {
                                placesLeft++;
                                toScore = 2*map[x][newY];
                            }
                            map[x][newY] += map[x][y];
                            map[x][y] = 0;
                            state = Action;
                        }
                    }
                }
            }
            break;
        case 'a':
            for ( int x = 1; x < size; x++ ){
                for ( int y = 0; y < size; y++ ){
                    if ( map[x][y] != 0 ){
                        int newX = checkA(x,y,map[x][y]);
                        if ( x != newX){
                            if ( map[newX][y] != 0 ) {
                                placesLeft++;
                                toScore = 2*map[newX][y];
                            }
                            map[newX][y] += map[x][y];
                            map[x][y] = 0;
                            state = Action;
                        }
                    }
                }
            }
            break;
        case 'd':
            for ( int x = size-2; x >= 0; x--){
                for ( int y = 0; y < size; y++ ) {
                    if ( map[x][y] != 0 ){
                        int newX = checkD(x,y,map[x][y]);
                        if ( x != newX){
                            if ( map[newX][y] != 0 ) {
                                placesLeft++;
                                toScore = 2*map[newX][y];
                            }
                            map[newX][y] += map[x][y];
                            map[x][y] = 0;
                            state = Action;
                        }
                    }
                }
            }
            break;
        default:
            break;
    }
    if ( placesLeft == 0 ) state = End;
    if ( toScore == 2048 ) state = Score;
    score += toScore;
}
