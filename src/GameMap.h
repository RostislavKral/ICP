//
// Created by jeza on 27.4.23.
//

#ifndef MYQTPROJECT_GAMEMAP_H
#define MYQTPROJECT_GAMEMAP_H
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <vector>
#include <QDebug>
#include <QKeyEvent>
#include "Player.h"

using namespace std;

class GameMap : public QWidget {
public:
    const int blockSize = 80;
    explicit GameMap(QWidget* parent = nullptr);
    void setPlayer(Player player);
    vector<vector<int>> map;
protected:
    static vector<vector<int>> loadMap(const string& filename);
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
private:
    Player player;

};
#endif //MYQTPROJECT_GAMEMAP_H
