/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main handle of GameMap
 * @file GameMap.cpp
 */

#include <cstring>
#include "GameMap.h"
#include "ImageHandler.h"
#include "GameReplay.h"
#include "Game.h"

using namespace std;


GameMap::GameMap(Game *setGame, QWidget *parent) : QWidget(parent) {
    mapFilename = "";
    game = setGame;
}

vector<vector<int>> GameMap::loadMap() {
    if (mapFilename.empty()) {
        std::cerr << "Undefined path to mapLocal" << std::endl;
        exit(EXIT_FAILURE);
    }

    keyDefined = false;
    std::cerr << mapFilename << endl;
    vector<vector<int>> mapLocal; // local var of mapLocal
    ifstream file(mapFilename); // local var of file

    if (file.is_open()) {
        int rows, cols;
        file >> rows >> cols;
        mapLocal.resize(rows, vector<int>(cols, 0));

        string line;
        getline(file, line); // přečte konec řádku po řádku s rozměry

        for (int y = 0; y < rows; y++) {
            getline(file, line);
            cerr << "line:  " << line << endl;
            for (int x = 0; x < cols; x++) {
                char c = line[x];
                if (c == 'X') {
                    mapLocal[y][x] = WALL; // zeď
                } else if (c == '.') {
                    mapLocal[y][x] = FOOD; // cesta
                } else if (c == '0') {
                    mapLocal[y][x] = PATH; // cesta bez jidla
                } else if (c == 'G') {
                    if (game->numGhosts == 0) {
                        game->numGhosts++;
                        mapLocal[y][x] = G_BLINKY; // duch blinky
                        game->initialPositions.g_blinky.setX(x);
                        game->initialPositions.g_blinky.setY(y);
                    } else if (game->numGhosts == 1) {
                        game->numGhosts++;
                        mapLocal[y][x] = G_PINKY; // duch pinky
                        game->initialPositions.g_pinky.setX(x);
                        game->initialPositions.g_pinky.setY(y);
                    } else if (game->numGhosts == 2) {
                        game->numGhosts++;
                        mapLocal[y][x] = G_INKY; // duch inky
                        game->initialPositions.g_inky.setX(x);
                        game->initialPositions.g_inky.setY(y);
                    } else if (game->numGhosts == 3) {
                        game->numGhosts++;
                        mapLocal[y][x] = G_CLYDE; // duch clyde
                        game->initialPositions.g_clyde.setX(x);
                        game->initialPositions.g_clyde.setY(y);
                    } else if (game->numGhosts == 4) {
                        std::cerr << "Maximum number of ghosts is 4 " << std::endl;
                        exit(EXIT_FAILURE);
                    }
                } else if (c == 'T') {
                    mapLocal[y][x] = FINISH; // cil
                    finishDefined = true;
                } else if (c == 'K') {
                    mapLocal[y][x] = KEY; // klic
                    keyDefined = true;
                } else if (c == 'S') {
                    if (game->pacmanDefined) {
                        std::cerr << "Double pacman find" << std::endl;
                        exit(EXIT_FAILURE);
                    }
                    mapLocal[y][x] = PACMAN; // start
                    game->pacmanDefined = true;
                    game->initialPositions.pacman.setX(x);
                    game->initialPositions.pacman.setY(y);
                }
            }
        }
        game->actualPositions.pacman = game->initialPositions.pacman;
        game->actualPositions.g_clyde = game->initialPositions.g_clyde;
        game->actualPositions.g_pinky = game->initialPositions.g_pinky;
        game->actualPositions.g_blinky = game->initialPositions.g_blinky;
        game->actualPositions.g_inky = game->initialPositions.g_inky;
        file.close();
    } else {
        std::cerr << "UNABLE TO ACCESS MAP FILE" << std::endl;
        std::cerr << "Error opening file: " << std::strerror(errno) << std::endl;
        exit(EXIT_FAILURE);
    }
    if (!game->pacmanDefined || !keyDefined || !finishDefined){
        std::cerr << "Map format error, pacman or key not found" << std::endl;
        exit(EXIT_FAILURE);
    }
    // nastaveni herni mapy
    setFixedSize(int(mapLocal[0].size() + 2) * blockSize, int(mapLocal.size() + 2) * blockSize);
    return mapLocal;
}

void GameMap::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);

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
                painter.drawPixmap(x * blockSize, y * blockSize,
                                   ImageHandler::getPixmap("pacman" + this->lastMove, blockSize));
            }
        }
    }
}


