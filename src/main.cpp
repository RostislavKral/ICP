#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include "GameReplay.h"
#include "GUI.h"

using namespace std;

int main(int argc, char* argv[]) {
    bool modeReplay = true;
    QApplication app(argc, argv);


    Player player;
    GameMap gameMap;
    GUI gui(&gameMap);

    player.setMap(&gameMap.map);
    gui.setPlayer(player);

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
