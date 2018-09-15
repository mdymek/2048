#include "map.cpp"
#include <fstream>

class Game {
private:
    Map* m_area;
public:
    Game( Map* );
    ~Game();

    void play( Map::State& );
    void movement( char, Map::State& );
    void end() const;
};
