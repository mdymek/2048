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

    Map ( int );
    ~Map();

    void random();
    void draw();
    void end() const;

    int getPlacesLeft() const;
    void setPlacesLeft(int);

    int checkW(int, int, int);
    int checkS(int, int, int);
    int checkA(int, int, int);
    int checkD(int, int, int);

    void movement(char);
};
