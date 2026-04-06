#include "imageio.h"
#include "converter.h"

bool ImageIO::setfolderPath(const QString& folderPath) {
    if(folderPath.isEmpty()){
        return false;
    }
    this->folderPath = folderPath;
    return true;
}

bool ImageIO::saveImage(const cv::Mat& image, const QString& imageName){
    if(folderPath.isEmpty() || imageName.isEmpty() || image.empty()){
        return false;
    }
    QString fullPath = folderPath + "/" + imageName + ".png";
    QImage img = Converter::MatToQImge(image);
    if (img.isNull()){
        return false;
    }
    return img.save(fullPath);
}

QString ImageIO::getPathToImage(const QString& imageName) const{
    return folderPath + "/" +imageName + ".png";
}
