//
// Created by xkralr06 on 4/27/23.
//

#include "Player.h"
#include <iostream>


Player::Player(){

};

void Player::setMap(std::vector<std::vector<int>>* map) {
    this->map = map;
}

Coordinates Player::getCoordinates() {
    int rows = this->map[0].size();
    int cols = this->map->size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if((*map)[i][j] == 6) return Coordinates{x=i, y=j};
        }
    }
}

void Player::move(int direction) {

    Coordinates coordinates = getCoordinates();
    int x = coordinates.x;
    int y = coordinates.y;
    std::cout << x << std::endl;
    std::cout << y << std::endl;

    if (direction == 0) {
        if(x <= 0) return;
        if( (*map)[x-1][y] != 0) return;
        (*map)[x][y] = 0;
        (*map)[x-1][y] = 6;

    } else if( direction == 1) {
        if (y <= 0) return;
        if( (*map)[x][y-1] != 0) return;

        (*map)[x][y] = 0;
        (*map)[x][y-1] = 6;


    } else if( direction == 2){
        if(x >= (*map)[0].size()) return;

        if( (*map)[x+1][y] != 0) return;

        (*map)[x][y] = 0;
        (*map)[x+1][y] = 6;


    } else if(direction == 3) {
        if(y >= (*map).size()) return;

        if( (*map)[x][y+1] != 0) return;

        (*map)[x][y] = 0;
        (*map)[x][y+1] = 6;


    }
}




