/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main handle of GameMap
 * @file GameMap.cpp
 */

#include "GameMap.h"
#include "ImageHandler.h"
#include "GameReplay.h"
#include "Game.h"

using namespace std;


GameMap::GameMap(Game *setGame, QWidget *parent) : QWidget(parent) {
    replay = false;
    mapFilename = "";
    game = setGame;
}


vector<vector<int>> GameMap::loadMap() {
    if (mapFilename.empty()) {
        std::cerr << "Undefined path to map" << std::endl;
        exit(EXIT_FAILURE);
    }
    vector<vector<int>> map;
    ifstream file(mapFilename);
    if (file.is_open()) {
        int rows, cols;
        file >> rows >> cols;
        map.resize(rows, vector<int>(cols, 0));

        string line;
        getline(file, line); // přečte konec řádku po řádku s rozměry

        for (int y = 0; y < rows; y++) {
            getline(file, line);
            for (int x = 0; x < cols; x++) {
                char c = line[x];
                if (c == 'X') {
                    map[y][x] = WALL; // zeď
                } else if (c == '.') {
                    map[y][x] = FOOD; // cesta
                } else if (c == '0') {
                    map[y][x] = PATH; // cesta bez jidla
                } else if (c == 'G') {
                    if (game->numGhosts == 0){
                        game->numGhosts++;
                        map[y][x] = G_BLINKY; // duch blinky
                    } else if (game->numGhosts == 1){
                        game->numGhosts++;
                        map[y][x] = G_PINKY; // duch blinky
                    } else if (game->numGhosts == 2){
                        game->numGhosts++;
                        map[y][x] = G_INKY; // duch blinky
                    } else if (game->numGhosts == 3){
                        game->numGhosts++;
                        map[y][x] = G_CLYDE; // duch blinky
                    } else if (game->numGhosts == 4) {
                        std::cerr << "Maximum number of ghosts is 4 " << std::endl;
                        exit(EXIT_FAILURE);
                    }
                } else if (c == 'T') {
                    map[y][x] = FINISH; // cil
                } else if (c == 'K') {
                    map[y][x] = KEY; // klic
                } else if (c == 'S') {
                    map[y][x] = PACMAN; // start
                }
            }
        }
        file.close();
    }
    setFixedSize((map[0].size() + 2) * blockSize, (map.size() + 2) * blockSize);
    return map;
}

void GameMap::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

    if (replay){

    }
    //cerr << "X: " << map[0].size() << "\t y: " << map.size() << endl;
    for (int y = 0; y < map.size() + 2; y++) {
        for (int x = 0; x < map[0].size() + 2; x++) {
            if (x == 0 || y == 0 || x == map[0].size() + 1 || y == map.size() + 1) {
                painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
            } else if (map[y - 1][x - 1] == WALL) {
                painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
            } else if (map[y - 1][x - 1] == FOOD) {
                painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::black); // jidlo
                painter.setBrush(Qt::white);
                painter.drawEllipse(x * blockSize + blockSize / 2, y * blockSize + blockSize / 2, blockSize / 4,
                                    blockSize / 4);
            } else if (map[y - 1][x - 1] == PATH) {
                painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::black); // cesta bez jidla
            } else if (map[y - 1][x - 1] == G_BLINKY) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("blinky_ghost", blockSize));
            } else if (map[y - 1][x - 1] == G_PINKY) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("pinky_ghost", blockSize));
            } else if (map[y - 1][x - 1] == G_INKY) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("inky_ghost", blockSize));
            } else if (map[y - 1][x - 1] == G_CLYDE) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("clyde_ghost", blockSize));
            } else if (map[y - 1][x - 1] == FINISH) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("finish", blockSize));
            } else if (map[y - 1][x - 1] == KEY) {
                painter.drawPixmap(x * blockSize, y * blockSize, ImageHandler::getPixmap("key", blockSize));
            } else if (map[y - 1][x - 1] == PACMAN) {
                //painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::magenta); // start
                painter.drawPixmap(x * blockSize, y * blockSize,
                                   ImageHandler::getPixmap("pacman" + this->lastMove, blockSize));
            }
        }
    }
}


