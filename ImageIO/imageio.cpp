#include "imageio.h"

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
    bool check = cv::imwrite(path.toStdString() + "/" + imageName.toStdString() + ".png", image);
    return check;
}

QString ImageIO::getPathToImage(const QString& imageName) const{
    return path + "/" +imageName + ".png";
}
