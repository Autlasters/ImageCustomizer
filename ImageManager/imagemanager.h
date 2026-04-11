#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <opencv2/opencv.hpp>
#include <Qstring>
#include <QStringList>

class ImageManager {
private:
    cv::Mat originalImage;
    cv::Mat processedImage;
public:
    bool loadImage(const QString& path);
    void applyFilter(const QString& filterName);
    void resetOriginalImage();
    void resetProcessedImage();
    const cv::Mat& getOriginalImage() const;
    const cv::Mat& getProcessedImage() const;
};

#endif // IMAGEMANAGER_H
