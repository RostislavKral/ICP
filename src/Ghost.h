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
    int x, y;
    int type;
    Game *game;

    explicit Ghost(int type, Game *game = nullptr);
    void move();

private:
    QPoint getCoordinates();
    vector<QPoint> dijkstra(QPoint start, QPoint dest);
};

#endif //MYQTPROJECT_GHOST_H
