//
// Created by jeza on 30.4.23.
//


#ifndef MYQTPROJECT_GAME_H
#define MYQTPROJECT_GAME_H

#include "GameMap.h"

#define FOOD 0
#define PATH  1
#define WALL 2
#define G_BLINKY 3
#define FINISH 4
#define KEY 5
#define PACMAN  6
#define G_PINKY 7
#define G_INKY 8
#define G_CLYDE 9

class GUI;
class Player;
class GameMap;

enum RunMode {
    INIT,
    PLAY,
    REPLAY_GAME,
    ENDGAME
};

class Game{
public:
    int numGhosts = 0;
    GameMap *gameMap;
    GUI *gui;
    Player *player;
    RunMode runMode;

    void setGameMap(GameMap *map);
    void setGui(GUI *gui);
    void setPlayer(Player *player);

    void WIN();

    void LOSE();

    void init();
};

#endif //MYQTPROJECT_GAME_H
