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

/**
 * @author Rostislav Kral
 * @brief getting Coordinates (QPoint) of the Player from map
 * @description getting Coordinates (QPoint) of the Player from map
 * @params
 * @return
 * */
QPoint Player::getCoordinates() const {
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

int Player::getScore() const  {
    return score;
}

void Player::resetScore()  {
    score = 0;
}

void Player::move(int direction) {
    if (direction == 4) return;
    QPoint coordinates = getCoordinates();
    int x = coordinates.x();
    int y = coordinates.y();
    //std::cout << x << "\t" << y << std::endl;

    int dx, dy;
    if (direction == 0) {
        if(x <= 0 ) return;
        if( (game->gameMap->map)[x-1][y] == WALL) return;

        dx = x-1;
        dy = y;


    } else if( direction == 1) {
        if(y <= 0  ) return;
        if( (game->gameMap->map)[x][y-1] == WALL) return;
        dx = x;
        dy = y-1;


    } else if( direction == 2){
        if(x >= (game->gameMap->map)[0].size() - 1 ) return;
        if( (game->gameMap->map)[x+1][y] == WALL) return;

        dx = x+1;
        dy = y;


    } else if(direction == 3) {
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
    } else if ((game->gameMap->map)[dx][dy] == FOOD) {
        score+=1;
    } else if ((game->gameMap->map)[dx][dy] == FINISH) {
        if(!this->hasKey) return;
        game->WIN();

    } else if ((game->gameMap->map)[dx][dy] == G_BLINKY ||
            (game->gameMap->map)[dx][dy] == G_PINKY ||
            (game->gameMap->map)[dx][dy] == G_INKY ||
            (game->gameMap->map)[dx][dy] == G_CLYDE) {
        if (game->numLives == 1) game->LOSE();
        else game->respawnGame();
        return;

    }

    (game->gameMap->map)[x][y] = PATH;
    (game->gameMap->map)[dx][dy] = PACMAN;
    game->actualPositions.pacman.setX(dx);
    game->actualPositions.pacman.setY(dy);
}




