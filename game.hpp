#include "map.cpp"
#include <fstream>

class Game {
private:
    Map* m_area;
public:
    Game( Map* );
    ~Game();

    void play( Map::State&, sf::RenderWindow& );
    void score( sf::RenderWindow& );
    void end( sf::RenderWindow& ) const;
    void movement( sf::Keyboard::Key, Map::State&, int& );
};
