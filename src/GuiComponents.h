//
// Created by jeza on 28.4.23.
//

#ifndef MYQTPROJECT_GUICOMPONENTS_H
#define MYQTPROJECT_GUICOMPONENTS_H

#include <QPushButton>

class GuiComponents {
public:
    GuiComponents();
    static QPushButton *createButton(const std::string &color, std::string text);
    static QLabel *createLabel(const std::string &color, std::string text);
    QPushButton *newGame;
    QPushButton *resetGame;
    QPushButton *loadGame;
    QLabel * scoreLabel;

};
#endif //MYQTPROJECT_GUICOMPONENTS_H
