/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Creates and handle all UI components
 * @file GUI.cpp
 */

#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "GUI.h"
#include "Game.h"
#include "GameReplay.h"

GUI::GUI(Game *game, QWidget *parent) : QMainWindow(parent) {
    score = 0;
    this->game = game;

    setWindowTitle("PacMan Game");
    setStyleSheet("background-color: black;");
}

void GUI::initGui() {

    createLayout();

    connectButtons();

    this->show();
}

void GUI::updateScore() {
    this->score = game->player->getScore();
    GC.scoreLabel->setText("Score: " + QString::number(score));
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (game->runMode != PLAY && game->runMode != PLAY_LOG) return;
    if (event->key() == Qt::Key_W) {
        game->nextMove = 0;
        game->gameMap->lastMove = "T";
    } else if (event->key() == Qt::Key_A) {
        game->nextMove = 1;
        game->gameMap->lastMove = "L";
    } else if (event->key() == Qt::Key_S) {
        game->nextMove = 2;
        game->gameMap->lastMove = "D";
    } else if (event->key() == Qt::Key_D) {
        game->nextMove = 3;
        game->gameMap->lastMove = "R";
    } else if (event->key() == Qt::Key_Escape){
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    }
    updateScore();

}

void GUI::startGame(){

    if (game->runMode != REPLAY_GAME) GC.logGame->isChecked() ? game->runMode = PLAY_LOG : game->runMode = PLAY;
    // todo remove cerr << game->runMode << endl;
    if(game->runMode != REPLAY_GAME)game->gameMap->map = game->gameMap->loadMap();
    if (game->runMode == REPLAY_GAME) {
        game->gameMap->map = game->gameReplay->getProgress();
        game->gameMap->setFixedSize((game->gameMap->map[0].size() + 2) * game->gameMap->blockSize,
                                    (game->gameMap->map.size() + 2) * game->gameMap->blockSize);
    }

    GC.endGameLabel->setVisible(false);
    GC.loadGame->setVisible(false);
    GC.logGame->setVisible(false);
    game->gameMap->setVisible(true);
    GC.scoreLabel->setVisible(true);
    GC.pacmanLives->setVisible(true);

    game->player->resetScore();
    updateScore();


}

void GUI::startReplay(){

};
void GUI::createLayout(){
    QVBoxLayout * containter = new QVBoxLayout();


    QHBoxLayout * mainNavigation = new QHBoxLayout();
    mainNavigation->addWidget(GC.newGame);
    mainNavigation->addWidget(GC.logGame);
    mainNavigation->addWidget(GC.loadGame);
    mainNavigation->addWidget(GC.endGame);

    QHBoxLayout * gameData = new QHBoxLayout();
    gameData->addWidget(GC.scoreLabel);
    gameData->addWidget(GC.pacmanLives);
    GC.pacmanLives->setVisible(false);
    GC.scoreLabel->setVisible(false);
    gameData->setSizeConstraint(QLayout::SetMinAndMaxSize);

    QVBoxLayout *gameLayout = new QVBoxLayout();
    GC.endGameLabel->setVisible(false);
    gameLayout->addWidget(GC.endGameLabel);
    game->gameMap->setVisible(false);
    gameLayout->addWidget(game->gameMap);

    containter->addLayout(mainNavigation);
    containter->addLayout(gameLayout);
    containter->addLayout(gameData);
    QWidget *centralW = new QWidget(this);
    // centralW->setLayout(gameLayout);
    centralW->setLayout(containter);
    setCentralWidget(centralW);
}

void GUI::printWin(){
    GC.endGameLabel->setText("You WON");
    GC.endGameLabel->setVisible(true);
    game->gameMap->setVisible(false);
    GC.scoreLabel->setVisible(false);
}

void GUI::printLose(){
    GC.endGameLabel->setText("You LOST");
    GC.endGameLabel->setVisible(true);
    game->gameMap->setVisible(false);
    GC.scoreLabel->setVisible(false);
}

void GUI::removeLife(){
    GC.removeLife();
    game->numLives--;
    // game->respawnGame();
}

void GUI::connectButtons() {
    QObject::connect(GC.loadGame, &QPushButton::clicked, [this]() {
        game->runMode = REPLAY_GAME;
        startGame();
//        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
//        std::string fileNameStr = (fileName).toStdString();
//        cerr << fileNameStr << endl;
//        if (!fileName.isEmpty()) {
//            //game->gameMap->mapFilename = fileNameStr;
//            //game->gameMap->map = game->gameMap->loadMap();
//            game->logFilename = fileNameStr;
//            game->runMode = REPLAY_GAME;
//        }
    });

    QObject::connect(GC.menu, &QMenu::triggered, this, [=](QAction* action) {
        qDebug() << action->text();
        if (action->text() == "Mapa 1") {
            game->reinitGame();
            game->gameMap->mapFilename = "../map.txt";
        }
        else if (action->text() == "Mapa 2") {
            game->reinitGame();
            game->gameMap->mapFilename = "../map2.txt";
        }
        else if (action->text() == "WIN"){
            printWin();
            // game->gameMap->mapFilename = "../map.txt";
            return ;
        }
        else exit(EXIT_FAILURE);
        startGame();
    });

    QObject::connect(GC.endGame, &QPushButton::clicked, [=]() {
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    });

}