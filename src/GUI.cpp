#include <QVBoxLayout>
#include <QPushButton>
#include "GUI.h"


GUI::GUI(GameMap *map, QWidget *parent) : QMainWindow(parent) {
//    scoreLabel = new QLabel("Score: 0", this);
//    scoreLabel->setGeometry(10, 10, 100, 30);
    score = 0;
    gameMap = map;

    setWindowTitle("PacMan Game");
}

void GUI::initGui() {
    QVBoxLayout * containter = new QVBoxLayout();

    QHBoxLayout * mainNavigation = new QHBoxLayout();
    mainNavigation->addWidget(GC.newGame);
    mainNavigation->addWidget(GC.resetGame);
    mainNavigation->addWidget(GC.loadGame);

    QVBoxLayout *gameLayout = new QVBoxLayout();
    gameLayout->addWidget(GC.scoreLabel);
    gameMap->setVisible(false);
    gameLayout->addWidget(gameMap);

    containter->addLayout(mainNavigation);
    containter->addLayout(gameLayout);
    QWidget *centralW = new QWidget(this);
    // centralW->setLayout(gameLayout);
    centralW->setLayout(containter);
    setCentralWidget(centralW);

    QObject::connect(GC.newGame, &QPushButton::clicked, [=]() { // Přiřazení funkce, která změní viditelnost prvků po stisknutí tlačítka
        gameMap->setVisible(true);
    });
    this->show();
}

void GUI::setGameMap(GameMap *gameMap1) {
    this->gameMap = gameMap1;
}

void GUI::updateGui() {
    updateScore();
    gameMap->repaint();
}

void GUI::updateScore() {
    this->score = player.getScore();
    GC.scoreLabel->setText("Score: " + QString::number(score));
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_W) {
        this->player.move(0);
        this->gameMap->lastMove = "T";
    } else if (event->key() == Qt::Key_A) {
        this->player.move(1);
        this->gameMap->lastMove = "L";
    } else if (event->key() == Qt::Key_S) {
        this->player.move(2);
        this->gameMap->lastMove = "D";
    } else if (event->key() == Qt::Key_D) {
        this->player.move(3);
        this->gameMap->lastMove = "R";
    } else if (event->key() == Qt::Key_Escape){
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    }
    updateScore();

}

void GUI::setPlayer(Player player) {
    this->player = player;
}
