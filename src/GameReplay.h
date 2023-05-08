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
    explicit GameReplay(Game *setGame);
    ~GameReplay();

    fstream file;

    void logProgress();

    void getProgress();

    int resetLines;

    int blockLen = 0;

    int lineNum;
private:
    Game *game;

    void openFile(string io);
};

#endif //MYQTPROJECT_GAMEREPLAY_H
