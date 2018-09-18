#include "cell.hpp"



Cell::Cell( int x, int y ){
    val = 0;
    changed = false;
    square.setSize(sf::Vector2f(100,100));
    square.setOutlineThickness(1);
    square.setOutlineColor(sf::Color(199, 208, 221));
    square.setFillColor(colors[val]);
    m_x = 102*y;
    m_y = 102*x;
    square.setPosition(sf::Vector2f(m_x, m_y));
}

Cell::~Cell(){}

void Cell::setVal( int x ){
    val = x;
    square.setFillColor(colors[val]);
}
int Cell::value() const{ return val; }

void Cell::change(){ changed = true; }
void Cell::unchange(){ changed = false; }

bool Cell::isUnchanged(){ return !changed; }

sf::RectangleShape Cell::getSquare() {
    changed = false;
    return square;
}
