#include <SFML/Graphics.hpp>

class Cell {
private:
    int val;
    bool changed;
    sf::RectangleShape square;
    int m_x;
    int m_y;
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
