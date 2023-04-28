//
// Created by jeza on 28.4.23.
//
#include <QLabel>
#include "GuiComponents.h"

GuiComponents::GuiComponents() {
    newGame = createButton("green", "Nová hra");
    resetGame = createButton("blue", "Nahrát Hry");
    loadGame = createButton("red", "Ukončit hru");

    scoreLabel = createLabel("red", "Score");
}

QPushButton* GuiComponents::createButton(const std::string& color, std::string text) {
    QPushButton *button = new QPushButton(QString::fromStdString(text));
    QString style = "QPushButton {"
                 "background-color: " + QString::fromStdString(color) + ";"
                 "border: none;"
                 "color: white;"
                 "padding: 15px 32px;"
                 "text-align: center;"
                 "text-decoration: none;"
                 "display: inline-block;"
                 "font-size: 16px;"
                 "margin: 4px 2px;"
                 "cursor: pointer;"
                 "}";
    button->setStyleSheet(style);
    return button;
}

QLabel * GuiComponents::createLabel(const std::string& color, const std::string text) {
    QLabel *label = new QLabel(QString::fromStdString(text));
    QString style = "color: " + QString::fromStdString(color) + ";"
                    "background-color: white;"
                    "font-size: 24px;"
                    "font-weight: bold;"
                    "border: 2px solid black;"
                    "padding: 10px;";
    label->setStyleSheet(style);
    return label;
}
