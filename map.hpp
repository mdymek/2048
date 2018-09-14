#include <iostream>
#include <cstdlib>
#include <vector>

class Map {
private:
    friend class Game;
    std::vector< std::vector <int> > map;
    int size;
    int score;
public:
    enum State {
        End = 0,
        Action = 2,
        Pass = 4,
        Score = 8
    };
    int placesLeft;

    Map ( int );
    ~Map();

    void random();
    void draw(State&);

    int checkW(int, int, int);
    int checkS(int, int, int);
    int checkA(int, int, int);
    int checkD(int, int, int);

};
