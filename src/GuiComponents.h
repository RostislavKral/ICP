//
// Created by jeza on 28.4.23.
//

#ifndef MYQTPROJECT_GUICOMPONENTS_H
#define MYQTPROJECT_GUICOMPONENTS_H
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
class GuiComponents {
public:
    GuiComponents();
    static QPushButton *createButton(const std::string &color, std::string text);
    static QLabel *createLabel(const std::string &color, std::string text);
    QMenu *menu;
    QToolButton *newGame;
    QPushButton *endGame;
    QPushButton *loadGame;
    QLabel * scoreLabel;
    QCheckBox * logGame;

    static QCheckBox *createCheckbox(std::string text);

    QToolButton *createQButton(const std::string &color, std::string text);
};
#endif //MYQTPROJECT_GUICOMPONENTS_H
