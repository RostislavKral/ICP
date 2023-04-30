//
// Created by jeza on 28.4.23.
//

#include <QListWidgetItem>
#include "GuiComponents.h"
#include "ImageHandler.h"

GuiComponents::GuiComponents() {
    newGame = createQButton("green", "Nová hra");
    // Create a QMenu
    menu = new QMenu();
    menu->addAction("Mapa 1");
    menu->addAction("Mapa 2");
    menu->addAction("WIN");

// Set the QMenu as the dropdown menu for the QToolButton
    newGame->setMenu(menu);
    newGame->setPopupMode(QToolButton::InstantPopup);
    endGame = createButton("red", "Ukončit hru");
    loadGame = createButton("blue", "Nahrát hru");

    scoreLabel = createLabel("red", "Score");
    endGameLabel = createLabel("blue", "You WIN");

    logGame = createCheckbox("Logovat hru");

    pacmanLives = new QListWidget();
    for (int i = 0; i < 6; ++i) {
        QListWidgetItem *item1 = new QListWidgetItem();
        QPixmap pixmap1 = ImageHandler::getPixmap("pacmanR", 32);
        item1->setIcon(QIcon(pixmap1));
        pacmanLives->addItem(item1);
    }
    pacmanLives->setIconSize(QSize(32,32));
    pacmanLives->setViewMode(QListWidget::IconMode);
    pacmanLives->setFixedHeight(32);
    pacmanLives->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GuiComponents::removeLife() const{
    pacmanLives->takeItem(0);
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
                 "}"
                 "QPushButton:disabled {"
                 "background-color: gray;}";
    button->setStyleSheet(style);
    return button;
}

QToolButton* GuiComponents::createQButton(const std::string& color, std::string text) {
    QToolButton *button = new QToolButton();
    button->setText(QString::fromStdString(text));
    QString style = "QToolButton {"
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
                                                                           "}"
                                                                           "QToolButton:disabled {"
                                                                           "background-color: gray;}";
    button->setStyleSheet(style);
    return button;
}

QLabel * GuiComponents::createLabel(const std::string& color, const std::string text) {
    QLabel *label = new QLabel(QString::fromStdString(text));
    QString style = "color: " + QString::fromStdString(color) + ";"
                    "background-color: transparent;"
                    "font-size: 24px;"
                    "font-weight: bold;"
                    "border: 2px solid black;";
    label->setStyleSheet(style);
    return label;
}

QCheckBox * GuiComponents::createCheckbox(std::string text){
    QCheckBox *checkBox = new QCheckBox(QString::fromStdString(text));
    QString style = "QCheckBox { color: white; } QCheckBox::indicator { border: 2px solid white; }";
    checkBox->setStyleSheet(style);
    return checkBox;
};

