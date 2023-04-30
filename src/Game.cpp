//
// Created by jeza on 30.4.23.
//

#include "Game.h"

void Game::setGameMap(GameMap *map) {
    gameMap = map;
}

void Game::setGui(GUI *setGui) {
    gui = setGui;
}

void Game::setPlayer(Player *setPlayer) {
    player = setPlayer;
}