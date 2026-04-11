#include <QByteArray>
#include "imageio.h"
#include "converter.h"

bool ImageIO::setFolderPath(const QString& folderPath) {
    if(folderPath.isEmpty()){
        return false;
    }
    this->folderPath = folderPath;
    return true;
}

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

QString ImageIO::getPathToImage(const QString& imageName) const{
    return folderPath + "/" +imageName + ".png";
}

const QStringList &ImageIO::getExtensions() const {
    return extensions;
}
