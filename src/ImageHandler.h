//
// Created by jeza on 27.4.23.
//
#include <string>
#include <QImage>
#include <QPixmap>


#ifndef MYQTPROJECT_IMAGEHANDLER_H
#define MYQTPROJECT_IMAGEHANDLER_H
class ImageHandler {
public:
    static QPixmap getPixmap(const std::string& name, int size);
};

#endif //MYQTPROJECT_IMAGEHANDLER_H