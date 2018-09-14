#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

class Map {
private:
    std::vector< std::vector <int> > map;
    int size;
    int score;
public:
    int placesLeft;

    Map ( int S ){
        for ( int i = 0; i < S; i++ ){
            std::vector<int> row;
            for ( int j = 0; j < S; j++ ) row.push_back(0);
            map.push_back(row);
        }
        size = S;
        score = 0;
        placesLeft = S*S;
    }
    ~Map(){}

    void random(){
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

    void draw(){
        system("cls");
        random();
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
    }

    void end(){
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

    int checkW(int x, int y, int val){
        int newY = y-1;
        if ( map[x][newY] == 0 && newY > 0) newY = checkW(x, newY, val);

        if (map[x][newY] == val || map[x][newY] == 0) return newY;
        else return newY+1;
    }

    int checkS(int x, int y, int val){
        int newY = y+1;
        if ( map[x][newY] == 0 && newY < size-1) newY = checkS(x, newY, val);

        if (map[x][newY] == val || map[x][newY] == 0) return newY;
        else return newY-1;
    }

    int checkA(int x, int y, int val){
        int newX = x-1;
        if ( map[newX][y] == 0 && newX > 0) newX = checkA(newX, y, val);

        if (map[newX][y] == val || map[newX][y] == 0) return newX;
        else return newX+1;
    }

    int checkD(int x, int y, int val){
        int newX = x+1;
        if ( map[newX][y] == 0 && newX < size-1) newX = checkD(newX, y, val);

        if (map[newX][y] == val || map[newX][y] == 0) return newX;
        else return newX-1;
    }


    void movement(char c){
        switch(c){
            case 'w':
                for ( int y = 1; y < size; y++ ){
                    for ( int x = 0; x < size; x++ ){
                        if ( map[x][y] != 0 ){
                            int newY = checkW(x,y,map[x][y]);
                            if ( y != newY){
                                if ( map[x][newY] != 0 ) {
                                    placesLeft++;
                                    score += 2*map[x][newY];
                                }
                                map[x][newY] += map[x][y];
                                map[x][y] = 0;
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
                                    score += 2*map[x][newY];
                                }
                                map[x][newY] += map[x][y];
                                map[x][y] = 0;
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
                                    score += 2*map[newX][y];
                                }
                                map[newX][y] += map[x][y];
                                map[x][y] = 0;
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
                                    score += 2*map[newX][y];
                                }
                                map[newX][y] += map[x][y];
                                map[x][y] = 0;
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
    }


};
// int placesLeft = 16;
// int score = 0;
