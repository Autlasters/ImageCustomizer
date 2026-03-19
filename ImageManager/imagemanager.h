#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <opencv2/opencv.hpp>
#include <Qstring>
#include "filters.h"

class ImageManager {
private:
    cv::Mat originalImage;
    cv::Mat processedImage;
public:
    bool loadImage(const QString& path);
    void applyFilter(const QString& filterName);
    cv::Mat getOriginalImage() const;
    cv::Mat getProcessedImage() const;
};

#endif // IMAGEMANAGER_H
