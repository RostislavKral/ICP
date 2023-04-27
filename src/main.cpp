#include <QApplication>
#include <QTimer>
#include "GameMap.h"
#include "Player.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    GameMap widget;
    Player player;
    player.setMap(&widget.map);
    widget.setPlayer(player);
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, &widget, [&widget, &player] {

    //    player.move();
        widget.repaint();
    });
    timer.start(100); // Trigger the event every second
    widget.show();


    int ret = QApplication::exec();

    return ret;
}
