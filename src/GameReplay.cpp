/**
 * @author Lukáš Ježek
 * @file GameReplay.cpp
 * @brief Handling saving and replaying game to/from file
 */

#include "GameReplay.h"

/**
 * @brief Contructor for GameReplay class
 * @param filename
 */
GameReplay::GameReplay(const std::string& filename) {
    file.open(filename, std::ios::app);
    if (file.fail() || !file){
        std::cerr << "Unable to open file" << std::endl;
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief Fuction logs map
 * @param map
 */
void GameReplay::logProgress(vector<vector<int>> map) {
    file << map.size() << " " << map[0].size() << std::endl;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            file << map[i][j];
        }
        file << endl;
    }
    file << "----" << endl;
}

vector<vector<int>> GameReplay::getProgress() {
    vector<vector<int>> map;
    int rows, cols;
    file >> rows >> cols;
    map.resize(rows, vector<int>(cols, 0));

    string line;
    getline(file, line); // přečte konec řádku po řádku s rozměry
    for (int y = 0; y < rows; y++) {
        getline(file, line);
        for (int x = 0; x < cols; x++) {
            int c = line[x];
            map[y][x] = c; // zeď
        }
    }
    return map;
}
