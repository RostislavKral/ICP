/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief File contains all Player logic
 * @file Player.cpp
 */

#include "Player.h"
#include "GUI.h"
#include <iostream>

Player::Player(Game *setGame){
    score = 0;
    this->game = setGame;

};

//void Player::setMap(std::vector<std::vector<int>>* map) {
//    this->map = map;
//}

QPoint Player::getCoordinates() {
    int rows = game->gameMap->map[0].size();
    int cols = game->gameMap->map.size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if((game->gameMap->map)[i][j] == 6){
                QPoint p(i, j);
                return p;
            }
        }
    }
}

int Player::getScore()  {
    return score;
}

void Player::resetScore()  {
    score = 0;
}

void Player::move(int direction) {

    QPoint coordinates = getCoordinates();
    int x = coordinates.x();
    int y = coordinates.y();
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    int dx, dy;
    if (direction == 0) {
       // if(x <= 0) return;
        if(x <= 0 ) return;
        if( (game->gameMap->map)[x-1][y] == WALL) return;

        dx = x-1;
        dy = y;


    } else if( direction == 1) {
       // if (y <= 0) return;
        if(y <= 0  ) return;
        if( (game->gameMap->map)[x][y-1] == WALL) return;
        dx = x;
        dy = y-1;


    } else if( direction == 2){
       // if(x >= (game->gameMap->map)[0].size()) return;
        if(x >= (game->gameMap->map)[0].size() - 1 ) return;
        if( (game->gameMap->map)[x+1][y] == WALL) return;

        dx = x+1;
        dy = y;


    } else if(direction == 3) {
        //if(y >= (game->gameMap->map).size()) return;
        if(y >= (game->gameMap->map).size() - 1 ) return;
        if( (game->gameMap->map)[x][y+1] == WALL) return;

        dx = x;
        dy = y+1;

    } else {
        dx = x;
        dy = y;
    }


    if((game->gameMap->map)[dx][dy] == KEY) {
        score += 100;
        this->hasKey = true;
    } else if ((game->gameMap->map)[dx][dy] == 0) {
        score+=1;
    } else if ((game->gameMap->map)[dx][dy] == FINISH) {
        if(this->hasKey == false) return;
        game->WIN();
        /*
         * TODO: Successfully finished the game
         *
         * */
    } else if ((game->gameMap->map)[dx][dy] == G_BLINKY ||
            (game->gameMap->map)[dx][dy] == G_PINKY ||
            (game->gameMap->map)[dx][dy] == G_INKY ||
            (game->gameMap->map)[dx][dy] == G_CLYDE) {
        game->LOSE();
        return;

        /*
         * TODO: Lost the game
         *
         * */
    }

    (game->gameMap->map)[x][y] = 1;
    (game->gameMap->map)[dx][dy] = 6;
}




