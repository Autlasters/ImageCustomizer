#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QString>
#include <QStringList>
#include <opencv2/opencv.hpp>

class ImageIO {
private:
    QString folderPath;
    QStringList extensions = {".png", ".jpg", ".jpeg", ".webp"};
public:
    bool setFolderPath(const QString& folderPath);
    bool saveImage(const cv::Mat& image, const QString& imageName, const QString& extension);
    QString getPathToImage(const QString& imageName) const;
    const QStringList& getExtensions() const;
};

#endif // IMAGEIO_H
