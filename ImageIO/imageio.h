#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QString>
#include <opencv2/opencv.hpp>

class ImageIO {
private:
    QString folderPath;
public:
    bool setfolderPath(const QString& folderPath);
    bool saveImage(const cv::Mat& image, const QString& imageName);
    QString getPathToImage(const QString& imageName) const;
};

#endif // IMAGEIO_H
