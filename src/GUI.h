#include <QWidget>
#include <QLabel>
#include "GameMap.h"

class GUI : public QWidget {
//Q_OBJECT
public:
    explicit GUI(GameMap *map, QWidget *parent = nullptr);

    void initGui();
    void setGameMap(GameMap *gameMap);

private:
    QLabel *scoreLabel;
    int score;
    GameMap *gameMap;

    void updateScore();

public slots:
    void updateGui();

};