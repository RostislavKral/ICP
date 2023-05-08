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


class Ghost {


public:
    /**
     * @brief type of the ghost (0-3)
     */
    int type;

    /**
     * @brief Path of entity
     */
    int lastPathEntity = PATH;

    /**
     * @brief Injected Game object
     */
    Game *game;


    /**
     * @brief Constructor for set initial values
     * @param type
     * @param game
     */
    explicit Ghost(int type, Game *game = nullptr);

    /**
     * @author Rostislav Kral
     * @brief Method for moving Ghost on the map
     * @description Method will rearrange entities on the map, map is located in this->game->gameMap (instance of 2D vector<int>)
     * @params
     * @return
     * */
    void move();

private:
    /**
    * @author Rostislav Kral
     * @brief getting Coordinates (QPoint) of the ghost from map
     * @description getting Coordinates (QPoint) of the ghost from map
     * @params
     * @return
     * */
    QPoint getCoordinates() const;

    /**
     * @author Rostislav Kral
     * @brief Method for bfs pathfinding
     * @description Method returns path to a Player, vector walkable is for objects on the map that are walkable
     * @params QPoint start, QPoint dest, vector<int> walkable
     * @return std::vector<QPoint>
     **/
    vector<QPoint> bfs(QPoint start, QPoint dest, const vector<int> &walkable);
};

#endif //MYQTPROJECT_GHOST_H
