//
// Created by xkralr06 on 4/27/23.
//

#ifndef MYQTPROJECT_PLAYER_H
#define MYQTPROJECT_PLAYER_H
#include <vector>
#include "Coordinates.h"
#include "QPoint"
#include "Game.h"
class GUI;
class Player {


public:
    int x,y;
    Game *game;
    Player(Game *game = nullptr);
    void move(int direction);
    int getScore() ;
    void resetScore();
private:
    QPoint getCoordinates();
    int score;
    bool hasKey = false;
};


#endif //MYQTPROJECT_PLAYER_H
