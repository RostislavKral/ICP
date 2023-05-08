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
    if (game->runMode != REPLAY_GAME && game->runMode != REPLAY_PAUSE)
        this->score = game->player->getScore();
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
    } else if (event->key() == Qt::Key_Escape) {
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    }
    updateScore();

}

void GUI::startGame() {
    if (game->runMode != REPLAY_GAME && game->runMode != REPLAY_PAUSE) {
        guiComponents.logGame->isChecked() ? game->runMode = PLAY_LOG : game->runMode = PLAY;
        game->gameMap->map = game->gameMap->loadMap();
    }

    if (game->runMode == REPLAY_GAME || game->runMode == REPLAY_PAUSE) {
        game->gameReplay->getProgress();

        if (game->gameMap->map.empty()) {
            std::cerr << "Error loading map " << std::endl;
            exit(EXIT_FAILURE);
        }

        try {
            game->gameMap->setFixedSize((game->gameMap->map[0].size() + 2) * game->gameMap->blockSize,
                                        (game->gameMap->map.size() + 2) * game->gameMap->blockSize);

        } catch (std::exception &exception) {
            std::cerr << exception.what() << std::endl;
        }
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


void GUI::createLayout() {
    QVBoxLayout *containter = new QVBoxLayout();


    QHBoxLayout *mainNavigation = new QHBoxLayout();
    mainNavigation->addWidget(guiComponents.newGame);
    mainNavigation->addWidget(guiComponents.logGame);
    mainNavigation->addWidget(guiComponents.replayGame);
    mainNavigation->addWidget(guiComponents.endGame);

    QHBoxLayout *gameData = new QHBoxLayout();
    gameData->addWidget(guiComponents.scoreLabel);
    gameData->addWidget(guiComponents.pacmanLives);
    guiComponents.pacmanLives->setVisible(false);
    guiComponents.scoreLabel->setVisible(false);
    gameData->setSizeConstraint(QLayout::SetMinAndMaxSize);

    QHBoxLayout *replayControls = new QHBoxLayout();
    replayControls->addWidget(guiComponents.prevReplay);
    replayControls->addWidget(guiComponents.nextReplay);
    replayControls->addWidget(guiComponents.pauseReplay);

    QVBoxLayout *gameLayout = new QVBoxLayout();
    guiComponents.endGameLabel->setVisible(false);
    gameLayout->addWidget(guiComponents.endGameLabel);
    game->gameMap->setVisible(false);
    gameLayout->addWidget(game->gameMap);

    containter->addLayout(mainNavigation);
    containter->addLayout(replayControls);
    containter->addLayout(gameLayout);
    containter->addLayout(gameData);
    QWidget *centralW = new QWidget(this);
    // centralW->setLayout(gameLayout);
    centralW->setLayout(containter);
    setCentralWidget(centralW);
}

void GUI::replayControlsVisible(bool status) const {
    guiComponents.prevReplay->setVisible(status);
    guiComponents.nextReplay->setVisible(status);
    guiComponents.pauseReplay->setVisible(status);
}

void GUI::printEndGame(const std::string &text) {
    guiComponents.endGameLabel->setText(QString::fromStdString(text));
    guiComponents.endGameLabel->setVisible(true);

    game->gameMap->setVisible(false);
    guiComponents.scoreLabel->setVisible(false);
    guiComponents.pacmanLives->setVisible(false);
}

void GUI::removeLife() {
    guiComponents.removeLife();
    game->numLives--;
}

void GUI::connectButtons() {
    QObject::connect(guiComponents.replayGame, &QPushButton::clicked, [this]() {
        game->runMode = REPLAY_PAUSE;
        guiComponents.newGame->setVisible(false);
        replayControlsVisible(true);

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
        std::string fileNameStr = (fileName).toStdString();
        cerr << fileNameStr << endl;

        if (!fileName.isEmpty()) game->logFilename = fileNameStr;

        game->runMode = REPLAY_GAME;
        startGame();
    });

    QObject::connect(guiComponents.menu, &QMenu::triggered, this, [=](QAction *action) {
        qDebug() << action->text();
        if (action->text() == "Mapa 1") {
            game->reinitGame();
            game->gameMap->mapFilename = "../map.txt";
        } else if (action->text() == "Mapa 2") {
            game->reinitGame();
            game->gameMap->mapFilename = "../map2.txt";
        } else if (action->text() == "WIN") {
            printEndGame("YOU WON");
            // game->gameMap->mapFilename = "../map.txt";
            return;
        } else exit(EXIT_FAILURE);
        startGame();
    });

    QObject::connect(guiComponents.endGame, &QPushButton::clicked, [=]() {
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    });

    QObject::connect(guiComponents.pauseReplay, &QPushButton::clicked, [=]() {
        if (game->runMode == REPLAY_GAME) {
            game->runMode = REPLAY_PAUSE;
            guiComponents.pauseReplay->setText("PLAY");
        } else {
            game->runMode = REPLAY_GAME;
            guiComponents.pauseReplay->setText("PAUSE");
        }
    });

    QObject::connect(guiComponents.nextReplay, &QPushButton::clicked, [=]() {
        if (game->runMode != ENDGAME) game->runMode = REPLAY_PAUSE;
        guiComponents.pauseReplay->setText("PLAY");
        game->gameReplay->resetLines = game->gameReplay->lineNum;
        game->gameReplay->getProgress();
    });

    QObject::connect(guiComponents.prevReplay, &QPushButton::clicked, [=]() {
        if (game->runMode != ENDGAME) game->runMode = REPLAY_PAUSE;
        guiComponents.pauseReplay->setText("PLAY");
        game->gameReplay->resetLines = game->gameReplay->lineNum - (2 * game->gameReplay->blockLen);
        game->gameReplay->getProgress();
        cerr << game->numLives << "   " << game->gui->score << endl;
    });
}

void GUI::closeEvent(QCloseEvent *event) {
    if (game->gameReplay->file.is_open()) game->gameReplay->file.close();
}
