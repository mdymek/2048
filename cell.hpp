#include <SFML/Graphics.hpp>

class Cell {
private:
    int val;
    bool changed;
    sf::RectangleShape square;
    int m_x;
    int m_y;

    static std::map< int, sf::Color > colors;
public:
    Cell( int, int );
    ~Cell();

    void setVal( int );
    int value() const;

    void change();
    void unchange();

    bool isUnchanged();
    sf::RectangleShape getSquare();
};

std::map< int, sf::Color> Cell::colors { { 0, sf::Color(255, 229, 198)  },
                                         { 2, sf::Color(255, 199, 132)  },
                                         { 4, sf::Color(244, 177, 97)   },
                                         { 8, sf::Color(255, 175, 81)   },
                                         { 16, sf::Color(255, 156, 76)  },
                                         { 32, sf::Color(255, 171, 104) },
                                         { 64, sf::Color(255, 143, 73)  },
                                         { 128, sf::Color(249, 132, 89) },
                                         { 256, sf::Color(234, 111, 65) },
                                         { 512, sf::Color(252, 109, 55) },
                                         { 1024, sf::Color(255, 115, 40)},
                                         { 2048, sf::Color(255, 151, 61)} };
