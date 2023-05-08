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
    if(game->runMode != REPLAY_GAME) this->score = game->player->getScore();
    guiComponents.scoreLabel->setText("Score: " + QString::number(score));
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (game->runMode != PLAY && game->runMode != PLAY_LOG) return;
    if (event->key() == Qt::Key_W) {
        game->pacmanNextMove = 0;
        game->gameMap->lastMove = "T";
    } else if (event->key() == Qt::Key_A) {
        game->pacmanNextMove = 1;
        game->gameMap->lastMove = "L";
    } else if (event->key() == Qt::Key_S) {
        game->pacmanNextMove = 2;
        game->gameMap->lastMove = "D";
    } else if (event->key() == Qt::Key_D) {
        game->pacmanNextMove = 3;
        game->gameMap->lastMove = "R";
    } else if (event->key() == Qt::Key_Escape){
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    }
    updateScore();

}

void GUI::startGame(){

    if (game->runMode != REPLAY_GAME) guiComponents.logGame->isChecked() ? game->runMode = PLAY_LOG : game->runMode = PLAY;
    // todo remove cerr << game->runMode << endl;
    if(game->runMode != REPLAY_GAME)game->gameMap->map = game->gameMap->loadMap();
    if (game->runMode == REPLAY_GAME) {
        game->gameMap->map = game->gameReplay->getProgress();
        game->gameMap->setFixedSize((game->gameMap->map[0].size() + 2) * game->gameMap->blockSize,
                                    (game->gameMap->map.size() + 2) * game->gameMap->blockSize);
    }

    guiComponents.endGameLabel->setVisible(false);
    guiComponents.replayGame->setVisible(false);
    guiComponents.logGame->setVisible(false);
    game->gameMap->setVisible(true);
    guiComponents.scoreLabel->setVisible(true);
    guiComponents.pacmanLives->setVisible(true);

    game->player->resetScore();
    updateScore();


}

void GUI::startReplay(){

};
void GUI::createLayout(){
    QVBoxLayout * containter = new QVBoxLayout();


    QHBoxLayout * mainNavigation = new QHBoxLayout();
    mainNavigation->addWidget(guiComponents.newGame);
    mainNavigation->addWidget(guiComponents.logGame);
    mainNavigation->addWidget(guiComponents.replayGame);
    mainNavigation->addWidget(guiComponents.endGame);

    QHBoxLayout * gameData = new QHBoxLayout();
    gameData->addWidget(guiComponents.scoreLabel);
    gameData->addWidget(guiComponents.pacmanLives);
    guiComponents.pacmanLives->setVisible(false);
    guiComponents.scoreLabel->setVisible(false);
    gameData->setSizeConstraint(QLayout::SetMinAndMaxSize);

    QVBoxLayout *gameLayout = new QVBoxLayout();
    guiComponents.endGameLabel->setVisible(false);
    gameLayout->addWidget(guiComponents.endGameLabel);
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
    guiComponents.endGameLabel->setText("You WON");
    guiComponents.endGameLabel->setVisible(true);
    game->gameMap->setVisible(false);
    guiComponents.scoreLabel->setVisible(false);
}

void GUI::printLose(){
    guiComponents.endGameLabel->setText("You LOST");
    guiComponents.endGameLabel->setVisible(true);
    game->gameMap->setVisible(false);
    guiComponents.scoreLabel->setVisible(false);
}

void GUI::removeLife(){
    guiComponents.removeLife();
    game->numLives--;
    // game->respawnGame();
}

void GUI::connectButtons() {
    QObject::connect(guiComponents.replayGame, &QPushButton::clicked, [this]() {
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

    QObject::connect(guiComponents.menu, &QMenu::triggered, this, [=](QAction* action) {
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

    QObject::connect(guiComponents.endGame, &QPushButton::clicked, [=]() {
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    });

}