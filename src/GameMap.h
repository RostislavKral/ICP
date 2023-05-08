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
    /**
     * @brief Size in pixels of one block
     */
    const int blockSize = 30;

    /**
     * @brief Constructor sets initial values of class, empty filename
     * @param setGame
     * @param parent
     */
    explicit GameMap(Game *setGame, QWidget *parent = nullptr);

    /**
     * @brief Variable stores whole game map in 2D array
     */
    vector<vector<int>> map;

    /**
     * @brief Last Move of pacman
     */
    string lastMove = "R";

    /**
     * @brief File name of map
     */
    std::string mapFilename;

    /**
     * @brief Function loads map from file
     * @return
     */
    vector<vector<int>> loadMap();

protected:
    /**
     * @brief Function draws all content of map, including ghosts, pacman, walls, key, exit
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;
private:
    /**
     * @brief Injected game object
     */
    Game *game;

};

#endif //MYQTPROJECT_GAMEMAP_H
