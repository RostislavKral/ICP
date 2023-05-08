/**
 * @authors Lukáš Ježek, Rostislav Král
 * @brief Header file for ImageHandler.cpp
 * @file ImageHandler.h
 */


#include <string>
#include <QImage>
#include <QPixmap>


#ifndef MYQTPROJECT_IMAGEHANDLER_H
#define MYQTPROJECT_IMAGEHANDLER_H

class ImageHandler {
public:
    /**
     * @brief Function returns pixmap of sele
     * @param name
     * @param size
     * @return
     */
    static QPixmap getPixmap(const std::string &name, int size);
};

#endif //MYQTPROJECT_IMAGEHANDLER_H
