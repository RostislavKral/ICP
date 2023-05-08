/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Generates QPixmap for icons
 * @file ImageHandler.cpp
 */

#include "ImageHandler.h"

QPixmap ImageHandler::getPixmap(const std::string &name, int size) {
    QPixmap fullImage;
    fullImage.load("images/icons.png");
    int width = 16;
    int height = 16;

    QPixmap finalImage;
    if (name == "pacmanR") finalImage = fullImage.copy((0 * 16) + 3, 0, width, height);
    else if (name == "pacmanL") finalImage = fullImage.copy((0 * 16) + 3, (1 * 16), width, height);
    else if (name == "pacmanT") finalImage = fullImage.copy((0 * 16) + 3, (2 * 16), width, height);
    else if (name == "pacmanD") finalImage = fullImage.copy((0 * 16) + 3, (3 * 16), width, height);
    else if (name == "blinky_ghost") finalImage = fullImage.copy((0 * 16) + 3, (4 * 16), width, height);
    else if (name == "pinky_ghost") finalImage = fullImage.copy((0 * 16) + 3, (5 * 16), width, height);
    else if (name == "inky_ghost") finalImage = fullImage.copy((0 * 16) + 3, (6 * 16), width, height);
    else if (name == "clyde_ghost") finalImage = fullImage.copy((0 * 16) + 3, (7 * 16), width, height);
    else if (name == "key") finalImage = fullImage.copy((9 * 16) + 3, (3 * 16), width, height);
    else if (name == "finish") finalImage = fullImage.copy((8 * 16) + 3, (3 * 16), width, height);

    return finalImage.scaled(size, size, Qt::KeepAspectRatio);
}