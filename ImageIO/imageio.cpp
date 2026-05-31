/*
 * imageio.cpp
 *
 * This source file implements the logic of the methods of the class ImageIO
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include <QByteArray>
#include "imageio.h"
#include "converter.h"

//Method to set the path to the saving folder
bool ImageIO::setFolderPath(const QString& folderPath) {
    if(folderPath.isEmpty()){
        return false;
    }
    this->folderPath = folderPath;
    return true;
}

//Method to save an image in a folder
bool ImageIO::saveImage(const cv::Mat& image, const QString& imageName, const QString& extension){
    if(folderPath.isEmpty() || image.empty() || imageName.isEmpty() || extension.isEmpty() ){
        return false;
    }

    QString fullPath = folderPath + "/" + imageName + extension;
    QString temp = extension.mid(1);
    QByteArray format = temp.toUpper().toUtf8();
    QImage imageToSave = Converter::MatToQImge(image);
    if (imageToSave.isNull()){
        return false;
    }
    return imageToSave.save(fullPath, format.constData(), 90);
}

//Method to get the path to an image
QString ImageIO::getPathToImage(const QString& imageName) const{
    return folderPath + "/" +imageName + ".png";
}

//Method to get the preferred saving image extension
const QStringList &ImageIO::getExtensions() const {
    return extensions;
}
