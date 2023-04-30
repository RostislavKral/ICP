#include <QWidget>
#include <QLabel>
#include "GameMap.h"
#include <QKeyEvent>
#include <QMainWindow>
#include "GuiComponents.h"
#include "Player.h"

class Player;
class GUI : public QMainWindow {
public:
    enum RunMode {
        NONE = 0,
        NORMAL = 1,
        LOG = 2,
        REPLAY = 3,
        ENDGAME = 4
    };
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