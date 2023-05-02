/**
 * @authors Lukáš Ježek, Rostislav Král
 * @file Ghost.cpp
 */

#include "Ghost.h"
#include "GUI.h"
#include <queue>
#include <map>
#include <algorithm>

bool operator>(const Node &a, const Node &b) {
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
            if ((game->gameMap->map)[i][j] == this->type) {
                QPoint p(i, j);
                return p;
            }
        }
    }
}



void Ghost::move() {
    QPoint coordinates = getCoordinates();
    QPoint pacmanCoord = this->game->player->getCoordinates();
    int x = coordinates.x();
    int y = coordinates.y();
    vector<int> walkable = {0, 1, 6}; // values that are walkable
    vector<QPoint> path = this->bfs(coordinates, pacmanCoord, walkable);
    int dx, dy;
    if (path.empty()) {
        return;
    } else {
        if (path.size() != 1) {
            dx = path[1].x();
            dy = path[1].y();
        } else {
            dx = path[0].x();
            dy = path[0].y();
        }

        /*if((game->gameMap->map)[dx][dy] == 0 ||
                (game->gameMap->map)[dx][dy] == 1)
        {*/

        if((game->gameMap->map)[dx][dy] == PACMAN)
        {
            if (game->numLives == 1) game->LOSE();
            else game->respawnGame();
        }

        int temp = (game->gameMap->map)[dx][dy];

        (game->gameMap->map)[x][y] = lastPathEntity;


        this->lastPathEntity = temp;
        if(type == G_BLINKY) {
            (game->gameMap->map)[dx][dy] = G_BLINKY;
            game->actualPositions.g_blinky.setX(dx);
            game->actualPositions.g_blinky.setY(dy);
        } else if(type == G_CLYDE) {
            (game->gameMap->map)[dx][dy] = G_CLYDE;
            game->actualPositions.g_clyde.setX(dx);
            game->actualPositions.g_clyde.setY(dy);
        } else if(type == G_INKY) {
            (game->gameMap->map)[dx][dy] = G_INKY;
            game->actualPositions.g_inky.setX(dx);
            game->actualPositions.g_inky.setY(dy);
        } else if(type == G_PINKY) {
            (game->gameMap->map)[dx][dy] = G_PINKY;
            game->actualPositions.g_pinky.setX(dx);
            game->actualPositions.g_pinky.setY(dy);
        }
        // }
     //   std::cout << "(" << path[0].x() << ", " << path[0].y() << ")" << std::endl;
    }
//std::cout << pacmanCoord.x() << "\t" << pacmanCoord.y() << std::endl;

//std::cout << "DUSAN" << this->type << "\t" << x << "\t" << y << std::endl;
}

vector<QPoint> Ghost::bfs(QPoint start, QPoint dest, const vector<int> &walkable) {

    vector<vector<int>> map = this->game->gameMap->map;
    vector<QPoint> path;
    vector<vector<bool>> visited(map.size(), vector<bool>(map[0].size(), false));
    queue<QPoint> q;
    std::map<int, QPoint> prev;
    int rows = map.size();
    int cols = map[0].size();
    q.push(start);
    if (start.x() < 0 || start.x() >= rows || start.y() < 0 || start.y() >= cols) {
        return {}; // start point not valid
    }
    visited[start.x()][start.y()] = true;

    while (!q.empty()) {
        QPoint curr = q.front();
        q.pop();

        if (curr == dest) {
            // Found destination, backtrack to get path
            path.push_back(curr);
            while (prev.count(curr.x() * map[0].size() + curr.y())) {
                curr = prev[curr.x() * map[0].size() + curr.y()];
                path.push_back(curr);
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto &dir: {QPoint(1, 0), QPoint(-1, 0), QPoint(0, 1), QPoint(0, -1)}) {
            QPoint next_pos = curr + dir;
            if (next_pos.x() >= 0 && next_pos.x() < map.size() && next_pos.y() >= 0 && next_pos.y() < map[0].size()
                && !visited[next_pos.x()][next_pos.y()]
                && find(walkable.begin(), walkable.end(), map[next_pos.x()][next_pos.y()]) != walkable.end()) {
                q.push(next_pos);
                visited[next_pos.x()][next_pos.y()] = true;
                prev[next_pos.x() * map[0].size() + next_pos.y()] = curr;
            }
        }
    }

    // No path found
    return path;
}
