#include "game_map.h"
using namespace std;


GameMap::GameMap(QWidget* parent) : QWidget(parent) {
        map = loadMap("../map.txt");
        setFixedSize((map[0].size() + 2) * blockSize, (map.size() + 2) * blockSize);
    }

vector<vector<int>> GameMap::loadMap(const string& filename) {
        vector<vector<int>> map;
        ifstream file(filename);
        if (file.is_open()) {
            int rows, cols;
            file >> rows >> cols;
            map.resize(rows, vector<int>(cols, 0));

            string line;
            getline(file, line); // přečte konec řádku po řádku s rozměry

            for (int y = 0; y < rows; y++) {
                getline(file, line);
                for (int x = 0; x < cols; x++) {
                    char c = line[x];
                    if (c == ' ') {
                        map[y][x] = 0; // cesta
                    } else if (c == 'X') {
                        map[y][x] = 1; // zeď
                    } else if (c == '.') {
                        map[y][x] = 0; // cesta
                    }
                }
            }
            file.close();
        }
        return map;
    }

void GameMap::paintEvent(QPaintEvent* event)  {
        QPainter painter(this);
        cerr << "X: " << map[0].size() << "\t y: " << map.size() << endl;
        for (int y = 0; y < map.size() + 2; y++) {
            for (int x = 0; x < map[0].size() + 2; x++) {
                if (x == 0 || y == 0 || x == map[0].size() + 1 || y == map.size() + 1) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
                } else if (map[y - 1][x - 1] == 1) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
                } else {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::black); // cesta
                }
            }
        }
    }