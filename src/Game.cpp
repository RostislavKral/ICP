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
    gameReplay = new GameReplay(this);

    ghosts[0] = new Ghost(G_BLINKY, this);
    ghosts[1] = new Ghost(G_PINKY, this);
    ghosts[2] = new Ghost(G_INKY, this);
    ghosts[3] = new Ghost(G_CLYDE, this);



    initPositions();

    gui->initGui();
}


Game::~Game() {
    delete gameMap;
    delete gui;
    delete player;
    delete gameReplay;
};

void Game::reinitGame(){
    initPositions();
    gameMap->mapFilename = "";
    gameMap->replay = false;
    gameMap->lastMove = "R";

    this->runMode = INIT;
    this->numLives = 6;
    this->pacmanDefined = false;
    this->numGhosts = 0;

    // gui->initGui();
    gui->createLayout();
}

void Game::initPositions(){
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
}


void Game::respawnGame(){
    gui->removeLife();
    // TODO delete debug
    std::cout << "init: " << initialPositions.g_blinky.x() << "\t" << initialPositions.g_blinky.y() << std::endl;
    std::cout << "actual: " << actualPositions.g_blinky.x() << "\t" << actualPositions.g_blinky.y() << std::endl;

    gameMap->map[initialPositions.g_blinky.y()][initialPositions.g_blinky.x()] = G_BLINKY;
    gameMap->map[actualPositions.g_blinky.x()][actualPositions.g_blinky.y()] = PATH;

    gameMap->map[initialPositions.g_clyde.y()][initialPositions.g_clyde.x()] = G_CLYDE;
    gameMap->map[actualPositions.g_clyde.x()][actualPositions.g_clyde.y()] = PATH;

    gameMap->map[initialPositions.g_inky.y()][initialPositions.g_inky.x()] = G_INKY;
    gameMap->map[actualPositions.g_inky.x()][actualPositions.g_inky.y()] = PATH;

    gameMap->map[initialPositions.g_pinky.y()][initialPositions.g_pinky.x()] = G_PINKY;
    gameMap->map[actualPositions.g_pinky.x()][actualPositions.g_pinky.y()] = PATH;

    gameMap->map[initialPositions.pacman.y()][initialPositions.pacman.x()] = PACMAN;
    gameMap->map[actualPositions.pacman.x()][actualPositions.pacman.y()] = PATH;

}

void Game::WIN(){
    runMode = ENDGAME;
    gui->printEndGame("YOU WON");
};

void Game::LOSE(){
    runMode = ENDGAME;
    gui->printEndGame("YOU LOST");
}