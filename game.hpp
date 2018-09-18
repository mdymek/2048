#include "map.cpp"
#include <fstream>

class Game {
private:
    Map* m_area;
public:
    Game( Map* );
    ~Game();

    void play( Map::State&, sf::RenderWindow& );
    void movement( sf::Keyboard::Key, Map::State& );
    void end() const;
};
