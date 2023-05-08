/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for GUI.cpp
 * @file GUI.h
 */

#include <QWidget>
#include <QLabel>
#include "GameMap.h"
#include <QKeyEvent>
#include <QMainWindow>
#include "GuiComponents.h"
#include "Player.h"
#include "Game.h"

class GUI : public QMainWindow {
public:
    // RunMode runMode;
    explicit GUI(Game *map, QWidget *parent = nullptr);

    void initGui();

    void updateGui();

    void connectButtons();

    void createLayout();

    void startGame();

    void printWin();

    void printLose();

    void removeLife();

    void updateScore();

    int score;

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Game *game;
    GuiComponents guiComponents;


    void startReplay();
};