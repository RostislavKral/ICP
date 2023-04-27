//
// Created by jeza on 27.4.23.
//

#ifndef MYQTPROJECT_GAME_MAP_H
#define MYQTPROJECT_GAME_MAP_H
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <fstream>
#include <iostream>
#include <vector>
#include <QDebug>

using namespace std;

class GameMap : public QWidget {
public:
    const int blockSize = 48;
    explicit GameMap(QWidget* parent = nullptr);
    vector<vector<int>> map;
protected:
    static vector<vector<int>> loadMap(const string& filename);
    void paintEvent(QPaintEvent* event) override;

};
#endif //MYQTPROJECT_GAME_MAP_H
