/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for GameMap.cpp
 * @file GameMap.h
 */

#ifndef MYQTPROJECT_GAMEMAP_H
#define MYQTPROJECT_GAMEMAP_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <vector>
#include <QDebug>


using namespace std;

class Game;
class GameMap : public QWidget {
public:
    const int blockSize = 30;

    explicit GameMap(Game *setGame, QWidget *parent = nullptr);

    vector<vector<int>> map;
    string lastMove = "R";
    std::string mapFilename;
    vector<vector<int>> loadMap();
    bool replay;
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    Game *game;

};

#endif //MYQTPROJECT_GAMEMAP_H
