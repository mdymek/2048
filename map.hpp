#include <iostream>
#include <cstdlib>
#include <vector>
#include "cell.cpp"

class Map {
private:
    friend class Game;
    std::vector< std::vector < Cell > > map;
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

    Map(int);
    ~Map();

    void random();
    void draw(State&);

    int checkY(int, int, int, int);
    int checkX(int, int, int, int);

    void move(int, int, State&);
};
