#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include <cstdlib>

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

    QObject::connect(&timer, &QTimer::timeout, &widget, [&widget] {

        if((rand()%2) % 2 == 0)
        widget.map[3][3] = 6;
        else widget.map[3][3] = 4;
        widget.repaint();
    });
    timer.start(100); // Trigger the event every second


    int ret = QApplication::exec();

    return ret;
}
