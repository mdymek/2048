#include "cell.hpp"

Cell::Cell( int x, int y ){
    val = 0;
    changed = false;
    square.setSize(sf::Vector2f(100,100));
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color(100, 250, 50));
    m_x = 100*x + 1;
    m_y = 100*y + 1;
    square.setPosition(sf::Vector2f(m_x, m_y));
}

Cell::~Cell(){}

void Cell::setVal( int x ){ val = x; }
int Cell::value() const{ return val; }

void Cell::change(){ changed = true; }
void Cell::unchange(){ changed = false; }

bool Cell::isUnchanged(){ return !changed; }

sf::RectangleShape Cell::getSquare() { return square; }
