#include "game.hpp"

Game::Game( Map* area ) { m_area = area; }
Game::~Game(){}

void Game::play( Map::State& state, sf::RenderWindow& window ){
    m_area->draw(state, window);
    if ( state == Map::Score ){
        score( window );
    }
    else if ( state == Map::End ){
        end( window );
    }
}

void Game::score( sf::RenderWindow& window ){
    sf::Font font;
    font.loadFromFile("ARBONNIE.ttf");

    sf::Text message;
    message.setFont(font);
    message.setFillColor(sf::Color::Black);
    message.setString( "Congratulations! You made 2048.\n Do you want to contiune playing? Y/N" );
    message.setPosition(30, 150);

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(380, 380));
    background.setFillColor(sf::Color(247, 209, 165));
    background.setPosition(sf::Vector2f(10,10));

    window.draw(background);
    window.draw(message);
}

void Game::end( sf::RenderWindow& window ) const {
    sf::Font font;
    font.loadFromFile("ARBONNIE.ttf");

    sf::Text message;
    message.setFont(font);
    message.setFillColor(sf::Color::Black);

    std::fstream file;
    file.open("score.txt");
    int highscore;
    file >> highscore;
    if ( m_area->m_score > highscore ) {
        message.setString("You lose! Your score is " + std::to_string(m_area->m_score) + ".\n You beat your highscore!");
        file.close();
        file.open("score.txt", std::ofstream::trunc);
        file.close();
        file.open("score.txt");
        file << m_area->m_score;
        file.close();
    }
    else {
        message.setString("  You lose! Your score is " + std::to_string(m_area->m_score)
                             + ".\nYour current highscore is " + std::to_string(highscore)
                             + ".\n                      ~end~");
        file.close();
    }

    message.setPosition(30, 150);

    sf::RectangleShape background;
    background.setSize(sf::Vector2f(380, 380));
    background.setFillColor(sf::Color(247, 209, 165));
    background.setPosition(sf::Vector2f(10,10));

    window.draw(background);
    window.draw(message);
}

void Game::movement( sf::Keyboard::Key direction, Map::State& state, int& noMove ){
    state = Map::Pass;
    switch(direction){
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            m_area->move(0, 1, state, noMove);
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            m_area->move(0, -1, state, noMove);
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            m_area->move(1, 0, state, noMove);
            break;
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            m_area->move(-1, 0, state, noMove);
            break;
        default:
            break;
    }
}
