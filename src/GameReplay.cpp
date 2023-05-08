/**
 * @author Lukáš Ježek
 * @file GameReplay.cpp
 * @brief Handling saving and replaying game to/from file
 */

#include "GameReplay.h"
#include "GUI.h"


GameReplay::GameReplay(Game *setGame) {
    game = setGame;
}

GameReplay::~GameReplay() {
    file.close();
};

void GameReplay::openFile(std::string io) {
    if (file.is_open()) return;

    if (game->logFilename.empty()) game->logFilename = "../log.txt";

    if (game->logFilename.empty() || (io != "write" && io != "read")) {
        std::cerr << "Log/Replay file name empty or invalid io operation \t" << io << game->logFilename << endl;
        exit(EXIT_FAILURE);
    }
    if (io == "read") {
        file.open(game->logFilename, std::ios::in);
        if (file.fail()) std::cerr << "Failed to open file to read" << std::endl;
        return;
    } else if (io == "write") {
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
    file << game->gameMap->map.size() << " " << game->gameMap->map[0].size() << " " << game->numLives << " "
         << game->gui->score << std::endl;

    for (int i = 0; i < game->gameMap->map.size(); i++) {
        for (int j = 0; j < game->gameMap->map[i].size(); j++) {
            file << game->gameMap->map[i][j];
        }
        file << endl;
    }
    // file.close();
}

void GameReplay::getProgress() {
    openFile("read");
    vector<vector<int>> map;

    if (file.is_open()) {
        if (resetLines != lineNum) {
            file.seekg(0);
            lineNum = 0;
            while (resetLines > lineNum) {
                std::string tmpLine;
                getline(file, tmpLine);
                lineNum++;
            }
        }

        int rows, cols, numLives, score;

        file >> rows >> cols >> numLives >> game->gui->score;

        if (game->numLives > numLives) game->gui->removeLife();


        if (file.eof() || rows > 250 || cols > 250) {
            std::cerr << "End of file before end" << std::endl;
            file.close();
            //exit(EXIT_FAILURE);
            game->runMode = ENDGAME;
            game->gui->replayControlsVisible(false);
            game->gui->printEndGame("REPLAY END\nYou can close this window");
            return;
        }
        map.resize(rows, vector<int>(cols, 0));

        string line;
        getline(file, line); // přečte konec řádku po řádku s rozměry
        lineNum++;

        for (int y = 0; y < rows; y++) {
            getline(file, line);
            lineNum++;
            for (int x = 0; x < cols; x++) {
                unsigned char c = line[x];
                int a = c - '0';
                map[y][x] = a; // start
            }
        }
    }
    if (blockLen == 0) blockLen = lineNum;
    resetLines = lineNum;
    game->gameMap->map = map;
}
