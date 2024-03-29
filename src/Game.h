/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for Game.cpp
 * @file Game.h
 */

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
class Ghost;
class GameReplay;

enum RunMode {
    INIT,
    PLAY,
    PLAY_LOG,
    REPLAY_GAME,
    REPLAY_PAUSE,
    ENDGAME
};

class Game{
public:
    Game();
    int numGhosts = 0;
    int numLives = 6;
    bool pacmanDefined = false;
    int pacmanNextMove = 4;
    int testAnimation = 0;
    std::string logFilename;
    GameMap *gameMap;
    GUI *gui;
    Player *player;
    RunMode runMode;
    GameReplay *gameReplay;
    Ghost *ghost;
    Ghost *ghosts[4];

    struct IPositions{
        QPoint pacman;
        QPoint g_blinky;
        QPoint g_pinky;
        QPoint g_inky;
        QPoint g_clyde;
    }initialPositions;

    struct APositions{
        QPoint pacman;
        QPoint g_blinky;
        QPoint g_pinky;
        QPoint g_inky;
        QPoint g_clyde;
    }actualPositions;

    void WIN();

    void LOSE();

    void respawnGame() const;
    ~Game();

    void initPositions();

    void reinitGame();
};

#endif //MYQTPROJECT_GAME_H
