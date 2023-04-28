//
// Created by xkralr06 on 4/27/23.
//

#ifndef MYQTPROJECT_PLAYER_H
#define MYQTPROJECT_PLAYER_H
#include <vector>
#include "Coordinates.h"
class Player {


public:
    int x,y;
    Player();
    std::vector<std::vector<int>>* map;
    void setMap(std::vector<std::vector<int>>* map);
    void move(int direction);
    int getScore() ;
private:
    Coordinates getCoordinates();
    int score;
    bool hasKey = false;

};


#endif //MYQTPROJECT_PLAYER_H
