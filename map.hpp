#include <iostream>
#include <cstdlib>
#include <vector>
#include "cell.cpp"

class Map {
private:
    friend class Game;
    std::vector< std::vector < Cell > > m_map;
    int m_size;
    int m_score;
    int m_placesLeft;
public:
    enum State {
        End = 0,
        Action = 2,
        Pass = 4,
        Score = 8
    };

    Map(int);
    ~Map();

    void random();
    void draw( State&, sf::RenderWindow& );

    bool inRange( int ) const;
    int checkY( int, int, int, int );
    int checkX( int, int, int, int );

    void move( int, int, State& );
};
