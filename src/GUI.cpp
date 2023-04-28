#include <QVBoxLayout>
#include "GUI.h"


GUI::GUI(GameMap *map, QWidget *parent) : QWidget(parent) {
    scoreLabel = new QLabel("Score: 0", this);
    scoreLabel->setGeometry(10, 10, 100, 30);
    score = 0;
    gameMap = map;

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(gameMap);
    layout->addWidget(scoreLabel);
    setLayout(layout);
}

void GUI::initGui() {
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
    scoreLabel->setText("Score: " + QString::number(score));
}