#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "GUI.h"
#include "Player.h"


GUI::GUI(GameMap *map, QWidget *parent) : QMainWindow(parent) {
//    scoreLabel = new QLabel("Score: 0", this);
//    scoreLabel->setGeometry(10, 10, 100, 30);
    score = 0;
    gameMap = map;
    runMode = NONE;

    setWindowTitle("PacMan Game");
    setStyleSheet("background-color: black;");
}

void GUI::initGui() {

    createLayout();

    connectButtons();

    this->show();
}

void GUI::updateScore() {
    this->score = player.getScore();
    GC.scoreLabel->setText("Score: " + QString::number(score));
}

void GUI::keyPressEvent(QKeyEvent *event) {
    if (runMode != NORMAL) return;
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

void GUI::startGame(){
    runMode = NORMAL;
    gameMap->map = gameMap->loadMap();

    GC.loadGame->setVisible(false);
    GC.logGame->setVisible(false);
    gameMap->setVisible(true);
    GC.scoreLabel->setVisible(true);
    GC.pacmanLives->setVisible(true);

    player.resetScore();
    updateScore();


}

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
    GC.winLabel->setVisible(false);
    gameLayout->addWidget(GC.winLabel);
    gameMap->setVisible(false);
    gameLayout->addWidget(gameMap);

    containter->addLayout(mainNavigation);
    containter->addLayout(gameLayout);
    containter->addLayout(gameData);
    QWidget *centralW = new QWidget(this);
    // centralW->setLayout(gameLayout);
    centralW->setLayout(containter);
    setCentralWidget(centralW);
}

void GUI::printWin(){
    runMode = ENDGAME;
    GC.winLabel->setVisible(true);
    gameMap->setVisible(false);
    GC.scoreLabel->setVisible(false);
}

void GUI::connectButtons() {
    QObject::connect(GC.loadGame, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
        std::string testS = (fileName).toStdString();
        cerr << testS << endl;
        if (!fileName.isEmpty()) {
            gameMap->mapFilename = testS;
            gameMap->map = gameMap->loadMap();
        }
    });

    QObject::connect(GC.menu, &QMenu::triggered, this, [=](QAction* action) {
        qDebug() << action->text();
        if (action->text() == "Mapa 1") gameMap->mapFilename = "../map.txt";
        else if (action->text() == "Mapa 2") gameMap->mapFilename = "../map2.txt";
        else if (action->text() == "WIN"){
            printWin();
            gameMap->mapFilename = "../map.txt";
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