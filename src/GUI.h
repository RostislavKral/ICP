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
    /**
     * @brief Constructor sets score to 0, sets Game object injection, sets windows title and background color
     * @param map
     * @param parent
     */
    explicit GUI(Game *map, QWidget *parent = nullptr);

    /**
     * @brief Creates layout of GUI, connect buttons in Qt, shows GUI
     */
    void initGui();

    /**
     * @brief Function connects all button to Qt watcher and watch for button press
     */
    void connectButtons();

    /**
     * @brief Inits all buttons and labels, sets them to layout and generate general layout, sets visibility of widgets
     */
    void createLayout();

    /**
     * @brief Sets initial setup for game PLAY or REPLAY, sets visibility of widgets, reset player score
     */
    void startGame();

    /**
     * @brief Remove one life from GUI and decrements game->numLives;
     */
    void removeLife();

    /**
     * @brief Updates score in GUI
     */
    void updateScore();

    /**
     * @brief Stores information about actual score
     */
    int score;

    /**
     * @brief Prints label from parameter and hide gameMap, scoreLabel and pacmanLives
     * @param text
     */
    void printEndGame(const string& text);

    /**
     * @brief Show or hide replay controls -> Previous, Next, Play/Pause button
     * @param status
     */
    void replayControlsVisible(bool status) const;

protected:
    /**
     * @brief Catch user input from keyboard, in this case W,A,S,D,ESC, if game mode is not PLAY/PLAY_LOG catches only ESC button
     * @param event
     */
    void keyPressEvent(QKeyEvent* event) override;

    /**
     * @brief Catches event of closing window by clicking to cross button
     * @param event
     */
    void closeEvent(QCloseEvent * event) override;

private:
    /**
     * @brief Injected Game object
     */
    Game *game;

    /**
     * @brief Injected GuiComponents object
     */
    GuiComponents guiComponents;

};