#include "imageio.h"
#include "converter.h"

bool ImageIO::setPath(const QString& path) {
    if(path.isEmpty()){
        return false;
    }
    this->path = path;
    return true;
}

bool ImageIO::saveImage(const cv::Mat& image, const QString& imageName){
    if(path.isEmpty() || imageName.isEmpty() || image.empty()){
        return false;
    }
    QString fullPath = path + "/" + imageName + ".png";
    QImage img = Converter::MatToQImge(image);
    if (img.isNull()){
        return false;
    }
    return img.save(fullPath);
}

QString ImageIO::getPathToImage(const QString& imageName) const{
    return path + "/" +imageName + ".png";
}
