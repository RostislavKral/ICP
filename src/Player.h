/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for Player.cpp
 * @file Player.h
 */

#ifndef MYQTPROJECT_PLAYER_H
#define MYQTPROJECT_PLAYER_H
#include <vector>
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
