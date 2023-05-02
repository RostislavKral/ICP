/**
 * @authors Lukáš Ježek, Rostislav Král
 * @file Ghost.cpp
 */

#include "Ghost.h"
#include "GUI.h"
#include <queue>
#include <unordered_map>


bool operator>(const Node& a, const Node& b) {
    return a.dist > b.dist;
}

Ghost::Ghost(int type, Game *setGame) {
    this->type = type;
    this->game = setGame;
}
QPoint Ghost::getCoordinates() {
    int rows = game->gameMap->map[0].size();
    int cols = game->gameMap->map.size();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if((game->gameMap->map)[i][j] == this->type){
                QPoint p(i, j);
                return p;
            }
        }
    }
}


void BFS()
{

}


void Ghost::move() {
    QPoint coordinates = getCoordinates();
    QPoint pacmanCoord = this->game->player->getCoordinates();
    int x = coordinates.x();
    int y = coordinates.y();
    vector<QPoint> path = dijkstra(coordinates, pacmanCoord);

    if (path.empty()) {
        return;
    } else {
        int dx = path[0].x();
        int dy = path[0].y();

        /*if((game->gameMap->map)[dx][dy] == 0 )
        {*/
            (game->gameMap->map)[dx][dy] = 3;
            game->actualPositions.g_blinky.setX(dx);

        game->actualPositions.g_blinky.setY(dy);
       // }
      std::cout << "(" << path[0].x() << ", " << path[0].y() << ")" << std::endl;
    }
    //std::cout << pacmanCoord.x() << "\t" << pacmanCoord.y() << std::endl;

    //std::cout << "DUSAN" << this->type << "\t" << x << "\t" << y << std::endl;
}

vector<QPoint> Ghost::dijkstra(QPoint start, QPoint dest) {

    vector<vector<int>> map = game->gameMap->map;

    int rows = map.size();
    int cols = map[0].size();
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols));
    vector<vector<bool>> visited(rows, vector<bool>(cols));
    queue<QPoint> q;
    q.push(start);
    if (start.x() < 0 || start.x() >= rows || start.y() < 0 || start.y() >= cols) {
        return {}; // start point not valid
    }
    visited[start.x()][start.y()] = true;

    while (!q.empty()) {
        QPoint curr = q.front();
        q.pop();

        if (curr == dest) {
            break;
        }

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }

                QPoint next_pos(curr.x() + dx, curr.y() + dy);

                if (next_pos.x() < 0 || next_pos.x() >= rows || next_pos.y() < 0 || next_pos.y() >= cols) {
                    continue;
                }

                if (visited[next_pos.x()][next_pos.y()]) {
                    continue;
                }

                int val = map[next_pos.x()][next_pos.y()];

                if (val == 1) {
                    continue;
                }

                parent[next_pos.x()][next_pos.y()] = {curr.x(), curr.y()};
                visited[next_pos.x()][next_pos.y()] = true;
                q.push(next_pos);
            }
        }
    }

    if (!visited[dest.x()][dest.y()]) {
        return {}; // destination not reachable
    }

    vector<QPoint> path;
    QPoint next_pos = dest;
    while (next_pos != start) {
        path.push_back(next_pos);
        next_pos = QPoint(parent[next_pos.x()][next_pos.y()].first, parent[next_pos.x()][next_pos.y()].second);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    return path;
}
