/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for Ghost.cpp
 * @file Ghost.h
 */

#ifndef MYQTPROJECT_GHOST_H
#define MYQTPROJECT_GHOST_H

#include <vector>
#include <QPoint>
#include "Game.h"
#include <limits>
const int INF = numeric_limits<int>::max();

struct Node {
    QPoint pos;
    int dist;
};
class Ghost {


public:
    int x, y, type;
    int lastPathEntity = PATH;
    Game *game;


    explicit Ghost(int type, Game *game = nullptr);
    void move();

private:
    QPoint getCoordinates();
    vector<QPoint> bfs(QPoint start, QPoint dest, const vector<int>& walkable);
};

#endif //MYQTPROJECT_GHOST_H
