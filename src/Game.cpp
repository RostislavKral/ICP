/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main game file, center of data
 * @file Game.cpp
 */

#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include "GameReplay.h"
#include "GUI.h"
#include "Game.h"
#include "Ghost.h"

Game::Game(){
    // GameReplay replay("../log.txt", modeReplay);
    gameMap = new GameMap(this);
    gui = new GUI(this);
    player = new Player(this);

    initialPositions.pacman.setX(0);
    initialPositions.pacman.setY(0);
    initialPositions.g_clyde.setX(0);
    initialPositions.g_clyde.setY(0);
    initialPositions.g_blinky.setX(0);
    initialPositions.g_blinky.setY(0);
    initialPositions.g_inky.setX(0);
    initialPositions.g_inky.setY(0);
    initialPositions.g_pinky.setX(0);
    initialPositions.g_pinky.setY(0);


    gui->initGui();
}


Game::~Game() {
    delete gameMap;
    delete gui;
    delete player;
};

void Game::setGameMap(GameMap *map) {
    gameMap = map;
}

void Game::setGui(GUI *setGui) {
    gui = setGui;
}

void Game::setPlayer(Player *setPlayer) {
    player = setPlayer;
}

void Game::respawnGame(){
    gui->removeLife();

    // TODO delete debug
    std::cout << "init: " << initialPositions.pacman.x() << "\t" << initialPositions.pacman.y() << std::endl;
    std::cout << "actual: " << actualPositions.pacman.x() << "\t" << actualPositions.pacman.y() << std::endl;

    gameMap->map[initialPositions.pacman.y()][initialPositions.pacman.x()] = PACMAN;
    gameMap->map[actualPositions.pacman.x()][actualPositions.pacman.y()] = PATH;

}

void Game::WIN(){
    runMode = ENDGAME;
    gui->printWin();
};

void Game::LOSE(){
    runMode = ENDGAME;
    gui->printLose();
}