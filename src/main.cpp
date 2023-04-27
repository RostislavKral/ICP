#include <QApplication>
#include "game_map.h"

using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GameMap widget;
    widget.show();
    return app.exec();
}
