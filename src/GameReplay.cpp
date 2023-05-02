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
GameReplay::GameReplay(Game *setGame) {
    game = setGame;
//    file.open(filename, std::ios::in);
//    if (file.fail() || !file) {
//        if (!modeReplay) {
//            std::cerr << "Unable to open file, try to create new log.txt" << std::endl;
//            try {
//                file.open(filename, fstream::in | fstream::out | fstream::trunc);
//                file << "";
//                file.close();
//            } catch (const exception &exception) {
//                cerr << "Err while trying to create new file" << std::endl;
//                cerr << exception.what() << std::endl;
//                exit(EXIT_FAILURE);
//            }
//        } else {
//            std::cerr << "Unable to open file, try to create new log.txt" << std::endl;
//            exit(EXIT_FAILURE);
//        }
//    } else if (!modeReplay) {
//        file.close();
//        file.open(filename, std::ios::trunc | std::ios::out);
//        file << "\n";
//        file.close();
//        file.open(filename, std::ios::app);
//    }
}

void GameReplay::openFile(std::string io){
    if (file.is_open()) return;
    // todo remove this, just for testing
    game->logFilename = "../log.txt";
    if (game->logFilename.empty() || (io != "write" && io != "read")){
        std::cerr << "Log/Replay file name empty or invalid io operation \t" << io << game->logFilename << endl;
        exit(EXIT_FAILURE);
    }
    if (io == "read"){
        file.open(game->logFilename, std::ios::in);
        if (file.fail()) std::cerr << "Failed to open file to read" << std::endl;
        return;
    } else if(io == "write") {
        file.open(game->logFilename, std::ios::trunc | std::ios::out);
        if (file.fail()) std::cerr << "Failed to open file to read" << std::endl;
        file << "";
        file.close();
        file.open(game->logFilename, std::ios::app);
    }
}

/**
 * @brief Fuction logs map
 * @param map
 */
void GameReplay::logProgress() {
    openFile("write");
    file << game->gameMap->map.size() << " " << game->gameMap->map[0].size() << std::endl;

    for (int i = 0; i < game->gameMap->map.size(); i++) {
        for (int j = 0; j < game->gameMap->map[i].size(); j++) {
            file << game->gameMap->map[i][j];
        }
        file << endl;
    }
    // file.close();
}

vector<vector<int>> GameReplay::getProgress() {
    openFile("read");
    vector<vector<int>> map;
    //ifstream file("../log.txt");
    if (file.is_open()) {
        int rows, cols;

        file >> rows >> cols;
        if (file.eof() || rows > 250 || cols > 250) {
            std::cerr << "End of file before end" << std::endl;
            file.close();
            exit(EXIT_FAILURE);
        }
        map.resize(rows, vector<int>(cols, 0));

        string line;
        getline(file, line); // přečte konec řádku po řádku s rozměry

        for (int y = 0; y < rows; y++) {
            getline(file, line);
            for (int x = 0; x < cols; x++) {
                unsigned char c = line[x];
                int a = c - '0';
                map[y][x] = a; // start
            }
        }
    }
    return map;
}
