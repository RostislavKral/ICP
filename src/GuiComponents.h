/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for GuiComponents.cpp
 * @file GuiComponents.h
 */

#ifndef MYQTPROJECT_GUICOMPONENTS_H
#define MYQTPROJECT_GUICOMPONENTS_H

#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QPixmap>
#include <QListWidget>

class GuiComponents {
public:
    /**
     * @brief Constructor creates all labels, buttons, menus and checkboxes in this class
     */
    GuiComponents();

    /**
     * @brief Function for creating button with predefined class, accepts color of button and it's text
     * @param color Color of button
     * @param text Text of button
     * @return
     */
    static QPushButton *createButton(const std::string &color, std::string text);

    /**
     * @brief Function for creating label with predefined class, accepts color of label and it's text
     * @param color
     * @param text
     * @return
     */
    static QLabel *createLabel(const std::string &color, std::string text);

    /**
     * @brief Function for creating checkbox with predefined class, accepts it's text as param
     * @param text
     * @return
     */
    static QCheckBox *createCheckbox(std::string text);

    /**
     * @brief
     * @param color
     * @param text
     * @return
     */
    QToolButton *createQButton(const std::string &color, std::string text);

    /**
     * @brief Removes one life from pacman lives widget
     */
    void removeLife() const;

    /**
     * @brief New game menu
     */
    QMenu *menu;

     /**
      * @brief New game button
      */
    QToolButton *newGame;

    /**
     * @brief End game button
     */
    QPushButton *endGame;

    /**
     * @brief Replay game button
     */
    QPushButton *replayGame;

    /**
     * @brief Show previous image in replay game button
     */
    QPushButton *prevReplay;

    /**
      * @brief Show next image in replay game button
     */
    QPushButton *nextReplay;

    /**
      * @brief Pause auto replay game button
     */
    QPushButton *pauseReplay;

    /**
     * @brief Score label
     */
    QLabel *scoreLabel;

    /**
     * @brief End Game label
     */
    QLabel *endGameLabel;

    /**
     * @brief Checkbox log game option
     */
    QCheckBox *logGame;

    /**
     * @brief Pacman lives widget list
     */
    QListWidget *pacmanLives;
};

#endif //MYQTPROJECT_GUICOMPONENTS_H
