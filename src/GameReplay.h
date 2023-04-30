/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for GameReplay.cpp
 * @file GameReplay.h
 */

#include <iostream>
#include <fstream>
#include <cctype>
#include "GameMap.h"

#ifndef MYQTPROJECT_GAMEREPLAY_H
#define MYQTPROJECT_GAMEREPLAY_H

class GameReplay {
public:
    explicit GameReplay(const std::string &filename, bool modeReplay);

    fstream file;

    void logProgress(vector<vector<int>> map);

    vector<vector<int>> getProgress();

};

#endif //MYQTPROJECT_GAMEREPLAY_H
