#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
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
    mainNavigation->addWidget(GC.loadGame);
    mainNavigation->addWidget(GC.endGame);

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


    connect(GC.loadGame, &QPushButton::clicked, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());
        std::string testS = (fileName).toStdString();
        cerr << testS << endl;
        if (!fileName.isEmpty()) {
            gameMap->map = GameMap::loadMap(testS);
        }
    });
    
    QObject::connect(GC.newGame, &QPushButton::clicked, [=]() { // Přiřazení funkce, která změní viditelnost prvků po stisknutí tlačítka
        gameMap->map = GameMap::loadMap();
        player.resetScore();
        updateScore();
        gameMap->setVisible(true);
    });

    QObject::connect(GC.endGame, &QPushButton::clicked, [=]() { // Přiřazení funkce, která změní viditelnost prvků po stisknutí tlačítka
        QObject::disconnect();
        exit(EXIT_SUCCESS);
    });

    this->show();
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
