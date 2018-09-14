#include "game.hpp"

Game::Game( Map* M ) { area = M; }
Game::~Game(){}

void Game::play( Map::State& state ){
    if ( state ) area->draw(state);
    if ( state == Map::Score ){
        std::cout << std::endl << "Congratulations! You made 2048." << std::endl << "Do you want to contiune playing? Y/N" << std::endl;
        char c;
        std::cin >> c;
        if ( c == 'Y' ) state = Map::Action;
        else state = Map::End;
    }
}

// void Game::movement(char c, Map::State& state){
//     int toScore = 0;
//     state = Map::Pass;
//     switch(c){
//         case 'w':
//             for ( int y = 1; y < area->size; y++ ){
//                 for ( int x = 0; x < area->size; x++ ){
//                     if ( area->map[x][y] != 0 ){
//                         int newY = area->checkW(x, y, area->map[x][y]);
//                         if ( y != newY){
//                             if ( area->map[x][newY] != 0 ) {
//                                 area->placesLeft++;
//                                 toScore = 2*area->map[x][newY];
//                             }
//                             area->map[x][newY] += area->map[x][y];
//                             area->map[x][y] = 0;
//                             state = Map::Action;
//                         }
//                     }
//                 }
//             }
//             break;
//         case 's':
//             for ( int y = area->size-2; y >= 0; y-- ){
//                 for ( int x = 0; x < area->size; x++ ){
//                     if ( area->map[x][y] != 0 ){
//                         int newY = area->checkS(x, y, area->map[x][y]);
//                         if ( y != newY){
//                             if ( area->map[x][newY] != 0 ) {
//                                 area->placesLeft++;
//                                 toScore = 2*area->map[x][newY];
//                             }
//                             area->map[x][newY] += area->map[x][y];
//                             area->map[x][y] = 0;
//                             state = Map::Action;
//                         }
//                     }
//                 }
//             }
//             break;
//         case 'a':
//             for ( int x = 1; x < area->size; x++ ){
//                 for ( int y = 0; y < area->size; y++ ){
//                     if ( area->map[x][y] != 0 ){
//                         int newX = area->checkA(x, y, area->map[x][y]);
//                         if ( x != newX){
//                             if ( area->map[newX][y] != 0 ) {
//                                 area->placesLeft++;
//                                 toScore = 2*area->map[newX][y];
//                             }
//                             area->map[newX][y] += area->map[x][y];
//                             area->map[x][y] = 0;
//                             state = Map::Action;
//                         }
//                     }
//                 }
//             }
//             break;
//         case 'd':
//             for ( int x = area->size-2; x >= 0; x--){
//                 for ( int y = 0; y < area->size; y++ ) {
//                     if ( area->map[x][y] != 0 ){
//                         int newX = area->checkD(x, y, area->map[x][y]);
//                         if ( x != newX){
//                             if ( area->map[newX][y] != 0 ) {
//                                 area->placesLeft++;
//                                 toScore = 2*area->map[newX][y];
//                             }
//                             area->map[newX][y] += area->map[x][y];
//                             area->map[x][y] = 0;
//                             state = Map::Action;
//                         }
//                     }
//                 }
//             }
//             break;
//         default:
//             break;
//     }
//     if ( area->placesLeft == 0 ) state = Map::End;
//     if ( toScore == 2048 ) state = Map::Score;
//     area->score += toScore;
// }

void Game::movement (char c, Map::State& state){
        state = Map::Pass;
        switch(c){
            case 'w':
                area->move(0,1,state);
                break;
            case 's':
                area->move(0,-1,state);
                break;
            case 'a':
                area->move(1,0,state);
                break;
            case 'd':
                area->move(-1,0,state);
                break;
            default:
                break;
        }
}

void Game::end() const {
    std::cout << std::endl << "You lose! Your score is " << area->score << "." << std::endl;
    std::fstream file;
    file.open("score.txt");
    int highscore;
    file >> highscore;
    if (area->score > highscore) {
        std::cout << "You beat your highscore!" << std::endl;

        file.close();
        file.open("score.txt", std::ofstream::trunc);
        file.close();
        file.open("score.txt");
        file << area->score;
        file.close();
    }
    else {
        std::cout << "Your current highscore is " << highscore << "." << std::endl;
        file.close();
    }
}
