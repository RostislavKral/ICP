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


using namespace std;

class GameMap : public QWidget {
public:
    const int blockSize = 70;
    explicit GameMap(QWidget* parent = nullptr);
    vector<vector<int>> map;
    string lastMove = "R";
protected:
    static vector<vector<int>> loadMap(const string& filename);
    void paintEvent(QPaintEvent* event) override;

};
#endif //MYQTPROJECT_GAMEMAP_H
