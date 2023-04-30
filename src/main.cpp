#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include "GameReplay.h"
#include "GUI.h"
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool modeReplay = true;
    QApplication app(argc, argv);

    Game game{};
    game.runMode = INIT;

    GameMap gameMap(&game);
    game.setGameMap(&gameMap);

    GUI gui(&game);
    game.setGui(&gui);

    Player player(&game);
    game.setPlayer(&player);

   // GameReplay replay("../log.txt", modeReplay);
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &gameMap, [&gameMap] {
        gameMap.repaint();
    });
    timer.start(10); // Trigger the event every 10ms

    gui.initGui();


    int ret = QApplication::exec();

    return ret;
}
