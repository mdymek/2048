#include "map.cpp"
#include <fstream>

class Game {
private:
    Map* area;
public:
    Game( Map* );
    ~Game();

    void play( Map::State& );
    void movement(char, Map::State& );
    void end() const;
};
