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
    const int blockSize = 50;

    explicit GameMap(QWidget *parent = nullptr);

    vector<vector<int>> map;
    string lastMove = "R";
    std::string mapFilename;
    vector<vector<int>> loadMap();
    bool replay;
protected:
    void paintEvent(QPaintEvent *event) override;


};

#endif //MYQTPROJECT_GAMEMAP_H
