#include "map.hpp"
#include <iostream>
Map::Map( int size ) {
    m_size = size;
    m_score = 0;
    m_placesLeft = size*size;

    for ( int y = 0; y < size; y++ ){
        std::vector<Cell> row;
        for ( int x = 0; x < size; x++ ){
            Cell c(x, y);
            row.push_back(c);
        }
        m_map.push_back(row);
    }
}

Map::~Map(){}

void Map::random(){
    int x = rand() % 4;
    int y = rand() % 4;
    while ( m_map[x][y].value() != 0 ){
        x = rand() % 4;
        y = rand() % 4;
    }

    int c = rand() % 3;
    if ( c < 2 ) m_map[x][y].setVal(2);
    else m_map[x][y].setVal(4);
    m_placesLeft--;
}


void Map::draw( State& state, sf::RenderWindow& window ) {
    sf::Text number;
    sf::Text score;
    sf::Font font;

    font.loadFromFile("ARBONNIE.ttf");
    number.setFont(font);
    score.setFont(font);

    number.setFillColor(sf::Color::White);
    score.setFillColor(sf::Color::White);

    number.setStyle(sf::Text::Bold);
    score.setStyle(sf::Text::Bold);

    score.setCharacterSize(20);

    if ( state == Action ) random();
    for ( int y = 0; y < m_size; y++ ){
        for ( int x = 0; x < m_size; x++ ){
            window.draw(m_map[x][y].getSquare());
            number.setString(std::to_string(m_map[x][y].value()));
            number.setPosition(sf::Vector2f(102*x + 50 - number.getLocalBounds().width, 102*y + 50 - number.getLocalBounds().height));
            window.draw(number);
        }
    }
    score.setString("score: " + std::to_string(m_score));
    score.setPosition(sf::Vector2f(0,0));
    window.draw(score);
}

bool Map::inRange( int v ) const{
    return (v >= 0 && v < m_size);
}

int Map::checkY( int x, int y, int shift, int val ){
    int newY = y-shift;
    if (inRange(newY) && m_map[x][newY].value() == 0 ) newY = checkY(x, newY, shift, val);

    if ( inRange(newY) &&  m_map[x][newY].isUnchanged() &&
       ( m_map[x][newY].value() == val || m_map[x][newY].value() == 0 ))
    {
        return newY;
    }
    else return newY+shift;
}

int Map::checkX( int x, int y, int shift, int val ){
    int newX = x-shift;
    if ( inRange(newX) && m_map[newX][y].value() == 0 ) newX = checkX(newX, y, shift, val);

    if ( inRange(newX) && m_map[newX][y].isUnchanged() &&
       ( m_map[newX][y].value() == val || m_map[newX][y].value() == 0 ))
    {
        return newX;
    }
    else return newX+shift;
}

void Map::move( int shiftX, int shiftY, State& state ){
    int toScore = 0;
    if ( shiftX == 0 ){
        for ( int x = 0; x < m_size; x++ ){
            for ( int y = (m_size + shiftY)%m_size; inRange(y); y += shiftY ){
                if ( m_map[x][y].value() != 0 ){
                    int newY = checkY(x, y, shiftY, m_map[x][y].value());
                    if ( y != newY ){
                        if ( m_map[x][newY].value() != 0 ) {
                            m_placesLeft++;
                            toScore = 2*m_map[x][newY].value();
                            m_map[x][newY].change();
                        }
                        m_map[x][newY].setVal(m_map[x][newY].value() + m_map[x][y].value());
                        m_map[x][y].setVal(0);
                        state = Map::Action;
                    }
                }
            }
        }
    }
    else {
        for ( int y = 0; y < m_size; y++ ){
            for ( int x = (m_size + shiftX)%m_size; inRange(x); x += shiftX ){
                if ( m_map[x][y].value() != 0 ){
                    int newX = checkX(x, y, shiftX, m_map[x][y].value());
                    if ( x != newX ){
                        if ( m_map[newX][y].value() != 0 ) {
                            m_placesLeft++;
                            toScore = 2*m_map[newX][y].value();
                            m_map[newX][y].change();
                        }
                        m_map[newX][y].setVal(m_map[newX][y].value() + m_map[x][y].value());
                        m_map[x][y].setVal(0);
                        state = Map::Action;
                    }
                }
            }
        }
    }
    if ( m_placesLeft == 0 ) state = End;
    if ( toScore == 2048 ) state = Score;
    m_score += toScore;
}
