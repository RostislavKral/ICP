/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for GameReplay.cpp
 * @file GameReplay.h
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include "Game.h"

#ifndef MYQTPROJECT_GAMEREPLAY_H
#define MYQTPROJECT_GAMEREPLAY_H

class GameReplay {
public:
    /**
     * @brief Contructor for GameReplay class, sets injected Game object
     * @param filename
     */
    explicit GameReplay(Game *setGame);

    /**
     * @brief Destructor closes log file
     */
    ~GameReplay();

    /**
     * @brief Local variable for stream from log file
     */
    fstream file;

    /**
     * @brief Function stores log to log.txt file from game.gameMap.map
     */
    void logProgress();

    /**
     * @brief Function loads log from log file to game.gameMap.map object
     */
    void getProgress();

    /**
     * @brief Stores information of lines in case of prev/next replay image
     */
    int resetLines;

    /**
     * @brief Number of rows in log file for one image
     */
    int blockLen = 0;

    /**
     * @brief Stores information about processed lines
     */
    int lineNum;
private:
    /**
     * @brief Injected Game object
     */
    Game *game;

    /**
     * @brief Function opens log file for read/write depends on param, if already opened, returns
     * @param io accept read/write std::string
     */
    void openFile(string io);
};

#endif //MYQTPROJECT_GAMEREPLAY_H
