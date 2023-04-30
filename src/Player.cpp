//
// Created by xkralr06 on 4/27/23.
//

#include "Player.h"
#include "GUI.h"
#include <iostream>


Player::Player(GUI *gui){
    score = 0;
    this->gui = gui;

};

void Player::setMap(std::vector<std::vector<int>>* map) {
    this->map = map;
}

QPoint Player::getCoordinates() {
    int rows = this->map[0].size();
    int cols = this->map->size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if((*map)[i][j] == 6){
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
        if( (*map)[x-1][y] == WALL) return;

        dx = x-1;
        dy = y;


    } else if( direction == 1) {
       // if (y <= 0) return;
        if(y <= 0  ) return;
        if( (*map)[x][y-1] == WALL) return;
        dx = x;
        dy = y-1;


    } else if( direction == 2){
       // if(x >= (*map)[0].size()) return;
        if(x >= (*map)[0].size() - 1 ) return;
        if( (*map)[x+1][y] == WALL) return;

        dx = x+1;
        dy = y;


    } else if(direction == 3) {
        //if(y >= (*map).size()) return;
        if(y >= (*map).size() - 1 ) return;
        if( (*map)[x][y+1] == WALL) return;

        dx = x;
        dy = y+1;

    } else {
        dx = x;
        dy = y;
    }


    if((*map)[dx][dy] == KEY) {
        score += 100;
        this->hasKey = true;
    } else if ((*map)[dx][dy] == 0) {
        score+=1;
    } else if ((*map)[dx][dy] == FINISH) {
        if(this->hasKey == false) return;
        gui->printWin();
        /*
         * TODO: Successfully finished the game
         *
         * */
    } else if ((*map)[dx][dy] == 3) {
        gui->printLose();
        return;

        /*
         * TODO: Lost the game
         *
         * */
    }

    (*map)[x][y] = 1;
    (*map)[dx][dy] = 6;
}




