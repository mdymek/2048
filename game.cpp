#include "game.hpp"

Game::Game( Map* area ) { m_area = area; }
Game::~Game(){}

void Game::play( Map::State& state, sf::RenderWindow& window ){
    if ( state ) m_area->draw(state, window);
    if ( state == Map::Score ){
        std::cout << std::endl << "Congratulations! You made 2048." << std::endl << "Do you want to contiune playing? Y/N" << std::endl;
        char c;
        std::cin >> c;
        if ( c == 'Y' ) state = Map::Action;
        else state = Map::End;
    }
}

void Game::movement( char c, Map::State& state ){
        state = Map::Pass;
        switch(c){
            case 'w':
                m_area->move(0,1,state);
                break;
            case 's':
                m_area->move(0,-1,state);
                break;
            case 'a':
                m_area->move(1,0,state);
                break;
            case 'd':
                m_area->move(-1,0,state);
                break;
            default:
                break;
        }
}

void Game::end() const {
    std::cout << std::endl << "You lose! Your score is " << m_area->m_score << "." << std::endl;
    std::fstream file;
    file.open("score.txt");
    int highscore;
    file >> highscore;
    if ( m_area->m_score > highscore ) {
        std::cout << "You beat your highscore!" << std::endl;

        file.close();
        file.open("score.txt", std::ofstream::trunc);
        file.close();
        file.open("score.txt");
        file << m_area->m_score;
        file.close();
    }
    else {
        std::cout << "Your current highscore is " << highscore << "." << std::endl;
        file.close();
    }
}
