#include <QWidget>
#include <QLabel>
#include "GameMap.h"
#include <QKeyEvent>
#include <QMainWindow>
#include "GuiComponents.h"
#include "Player.h"
#include "Game.h"

class Player;
class GUI : public QMainWindow {
public:
    RunMode runMode;
    explicit GUI(GameMap *map, QWidget *parent = nullptr);

    void initGui();
    void setPlayer(Player player);

protected:
    void keyPressEvent(QKeyEvent* event) override;
private:
    bool gameStarted;

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

    void printWin();

    void printLose();
};