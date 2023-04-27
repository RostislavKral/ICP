#include <QApplication>
#include <QTimer>
#include "game_map.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GameMap widget;
    widget.show();
    widget.
//    QTimer timer;
//    QObject::connect(&timer, QTimer::timeout,[&]()){
//
//    }
//    timer.start(50);
    return QApplication::exec();
}
