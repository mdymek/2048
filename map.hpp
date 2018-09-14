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
    void end() const;

    int getScore() const;
    int getPlacesLeft() const;
    void setPlacesLeft(int);

    int checkW(int, int, int);
    int checkS(int, int, int);
    int checkA(int, int, int);
    int checkD(int, int, int);

    void movement(char, State&);
};
