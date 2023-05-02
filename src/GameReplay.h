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


    fstream file;

    void logProgress();

    vector<vector<int>> getProgress();
private:
    Game *game;

    void openFile(string io);
};

#endif //MYQTPROJECT_GAMEREPLAY_H
