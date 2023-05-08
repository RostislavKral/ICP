/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for Player.cpp
 * @file Player.h
 */

#ifndef MYQTPROJECT_PLAYER_H
#define MYQTPROJECT_PLAYER_H

#include <vector>
#include "QPoint"
#include "Game.h"

class GUI;

class Player {


public:
    Game *game;

    /**
     * @brief Constructs player sets Game object injection
     * @param game
     */
    explicit Player(Game *game = nullptr);

    /**
     * @brief Moving the player on the map
     * @description Moving the player, direction can be integer 0 - 3, W - 0, A - 1, S - 2, D - 3.
     *              We are calculating derivative and if is it possible it will move Player in direction he wanted to move.
     * @params
     * @return
     * */
    void move(int direction);

    /**
     * @brief Returns player's score
     * @return
     */
    int getScore() const;

    /**
     * @brief Resets player score to 0
     */
    void resetScore();

    /**
     * @brief Returns coordinates of pacman in map
     * @return
     */
    QPoint getCoordinates() const;

private:
    int score;
    bool hasKey = false;
};


#endif //MYQTPROJECT_PLAYER_H
