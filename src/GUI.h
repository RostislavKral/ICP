#include <QWidget>
#include <QLabel>
#include "GameMap.h"
#include "Player.h"
#include <QKeyEvent>
#include <QMainWindow>
#include "GuiComponents.h"


class GUI : public QMainWindow {
public:
    explicit GUI(GameMap *map, QWidget *parent = nullptr);

    void initGui();
    void setGameMap(GameMap *gameMap);
    void setPlayer(Player player);

protected:
    void keyPressEvent(QKeyEvent* event) override;


private:
    int score;
    GameMap *gameMap;
    Player player;
    GuiComponents GC;

    void updateScore();

public slots:
    void updateGui();

    void connectButtons();

    void createLayout();

    void startGame();
};