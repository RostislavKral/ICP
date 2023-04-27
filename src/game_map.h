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

using namespace std;

class GameMap : public QWidget {
public:
    const int blockSize = 35;
    explicit GameMap(QWidget* parent = nullptr);
protected:
    static vector<vector<int>> loadMap(const string& filename);
    void paintEvent(QPaintEvent* event) override;
private:
    vector<vector<int>> map;
};
#endif //MYQTPROJECT_GAME_MAP_H
