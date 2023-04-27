#include "GameMap.h"
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
                    if (c == 'X') {
                        map[y][x] = 1; // zeď
                    } else if (c == '.') {
                        map[y][x] = 0; // cesta
                    } else if (c == 'G') {
                        map[y][x] = 3; // duch
                    } else if (c == 'T') {
                        map[y][x] = 4; // cil
                    } else if (c == 'K') {
                        map[y][x] = 5; // klic
                    } else if (c == 'S') {
                        map[y][x] = 6; // start
                    }
                }
            }
            file.close();
        }
        return map;
    }

void GameMap::paintEvent(QPaintEvent* event)  {
    Q_UNUSED(event);
        QPainter painter(this);

//    QImage ghostImage;
//    ghostImage.load("../images/ghost_red.png");
        QPixmap images;
        images.load("../images/icons.png");
        QPixmap pacman = images.copy(0,0,16,16);
        pacman = pacman.scaled(blockSize, blockSize, Qt::KeepAspectRatio);

        cerr << "X: " << map[0].size() << "\t y: " << map.size() << endl;
        for (int y = 0; y < map.size() + 2; y++) {
            for (int x = 0; x < map[0].size() + 2; x++) {
                if (x == 0 || y == 0 || x == map[0].size() + 1 || y == map.size() + 1) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
                } else if (map[y - 1][x - 1] == 1) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::blue); // zed
                } else if (map[y - 1][x - 1] == 0){
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::black); // jidlo
                    painter.setBrush(Qt::white);
                    painter.drawEllipse(x * blockSize + blockSize/2, y * blockSize + blockSize/2, blockSize/4, blockSize/4);
                } else if (map[y - 1][x - 1] == 3) {
                    QImage image("../images/ghost_red.png");
                    image = image.scaled(blockSize, blockSize, Qt::KeepAspectRatio);
                    painter.drawImage(x * blockSize, y * blockSize, image);
                } else if (map[y - 1][x - 1] == 4) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::yellow); // cil
                } else if (map[y - 1][x - 1] == 5) {
                    painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::white); // klic
                } else if (map[y - 1][x - 1] == 6) {
                    //painter.fillRect(x * blockSize, y * blockSize, blockSize, blockSize, Qt::magenta); // start
                    painter.drawPixmap(x * blockSize, y * blockSize, pacman);
                }
            }
        }
    }