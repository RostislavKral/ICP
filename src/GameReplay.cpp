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
        std::cerr << "Unable to open file, try to create new log.txt" << std::endl;
        try {
            file.open(filename,  fstream::in | fstream::out | fstream::trunc);
            file <<"\n";
            file.close();
        } catch (const exception& exception){
            cerr << "Err while trying to create new file" << std::endl;
            cerr << exception.what() << std::endl;
            exit(EXIT_FAILURE);
        }
    } else {
        file.close();
        cerr << "asdasd";
        file.open(filename, std::ios::trunc | std::ios::out);
        file << "\n";
        file.close();
        file.open(filename, std::ios::app);
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
