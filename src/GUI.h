#include <QWidget>
#include <QLabel>
#include "GameMap.h"
#include "Player.h"
#include <QKeyEvent>

class GUI : public QWidget {
//Q_OBJECT
public:
    explicit GUI(GameMap *map, QWidget *parent = nullptr);

    void initGui();
    void setGameMap(GameMap *gameMap);
    void setPlayer(Player player);

protected:
    void keyPressEvent(QKeyEvent* event) override;


private:
    QLabel *scoreLabel;
    int score;
    GameMap *gameMap;
    Player player;

    void updateScore();

public slots:
    void updateGui();

};