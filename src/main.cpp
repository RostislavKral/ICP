/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main function TODO
 * @file main.cpp
 */

#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include "Ghost.h"
#include "GameReplay.h"
#include "GUI.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Game game;
    game.runMode = INIT;

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, game.gameMap, [&game] {
        game.player->move(game.nextMove);
        if(game.runMode == PLAY) {
            game.ghosts[0]->move();
            game.ghosts[1]->move();
            game.ghosts[2]->move();
            game.ghosts[3]->move();
        }
        if (game.runMode == PLAY_LOG) game.gameReplay->logProgress();
        else if (game.runMode == REPLAY_GAME) game.gameMap->map = game.gameReplay->getProgress();
        std::cerr << game.gameMap->map.size() << std::endl;
        game.gameMap->repaint();
    });
    timer.start(200); // Trigger the event every 10ms


    int ret = QApplication::exec();

    return ret;
}
