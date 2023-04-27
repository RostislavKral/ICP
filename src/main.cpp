#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include <cstdlib>
#include "GameReplay.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GameMap widget;
    widget.show();
    Player player;
    player.x = 5;
    player.y = 5;

    srand(std::time(nullptr));
    // Create a QTimer object to periodically trigger an event
    QTimer timer;
    GameReplay replay("../log.txt");
    QObject::connect(&timer, &QTimer::timeout, &widget, [&widget, &replay] {
        replay.logProgress(widget.map);
        if((rand()%2) % 2 == 0)
        widget.map[3][3] = 6;
        else widget.map[3][3] = 4;
        widget.repaint();
    });
    timer.start(1000); // Trigger the event every second


    int ret = QApplication::exec();

    return ret;
}
