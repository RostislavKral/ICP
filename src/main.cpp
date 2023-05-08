/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main function TODO
 * @file main.cpp
 */

#include <QApplication>
#include <QTimer>
#include <unistd.h>
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

    QTimer timer, timer2;
    QObject::connect(&timer, &QTimer::timeout, game.gameMap, [&game, &timer2, &timer] {
        game.player->move(game.pacmanNextMove);
        if(game.runMode == PLAY || game.runMode == PLAY_LOG) {
                game.ghosts[0]->move();
                game.ghosts[1]->move();
                game.ghosts[2]->move();
                game.ghosts[3]->move();
        }

        if (game.runMode == PLAY_LOG) game.gameReplay->logProgress();
        else if (game.runMode == REPLAY_GAME) game.gameReplay->getProgress();
        std::cerr << game.gameMap->map.size() << std::endl;
        if (game.runMode == ENDGAME){
            timer2.stop();
            timer.stop();
            //sleep(5);
            //exit(EXIT_SUCCESS);
        }
    });
    QObject::connect(&timer2, &QTimer::timeout, game.gameMap, [&game]{
        // if (game.runMode == REPLAY_PAUSE) game.gui->updateScore();
        game.gui->updateScore();
        if (game.runMode != ENDGAME && game.runMode != INIT) game.gameMap->repaint();
    });
    timer.start(750); // Trigger the event every 10ms
    timer2.start(10);


    int ret = QApplication::exec();

    return ret;
}
