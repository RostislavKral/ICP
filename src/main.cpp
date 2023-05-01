/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Main function TODO
 * @file main.cpp
 */

#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
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
        game.gameMap->repaint();
    });
    timer.start(10); // Trigger the event every 10ms


    int ret = QApplication::exec();

    return ret;
}
