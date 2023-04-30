/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main game file, center of data
 * @file Game.cpp
 */

#include "Game.h"
#include "Player.h"
#include "GameReplay.h"
#include "GUI.h"

void Game::setGameMap(GameMap *map) {
    gameMap = map;
}

void Game::setGui(GUI *setGui) {
    gui = setGui;
}

void Game::setPlayer(Player *setPlayer) {
    player = setPlayer;
}

void Game::WIN(){
    runMode = ENDGAME;
    gui->printWin();
};

void Game::LOSE(){
    runMode = ENDGAME;
    gui->printLose();
};