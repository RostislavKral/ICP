//
// Created by jeza on 27.4.23.
//
#include <iostream>
#include <fstream>
#include "GameMap.h"
#include <cctype>

#ifndef MYQTPROJECT_GAMEREPLAY_H
#define MYQTPROJECT_GAMEREPLAY_H
class GameReplay : public GameMap{
public:
    explicit GameReplay(const std::string& filename, bool modeReplay);
    fstream file;
    void logProgress(vector<vector<int>> map);
    vector<vector<int>> getProgress();
private:
    void saveProgress(vector<vector<int>> map);
    vector<vector<int>> loadProgress();
};
#endif //MYQTPROJECT_GAMEREPLAY_H
