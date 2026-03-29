#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <opencv2/opencv.hpp>
#include <Qstring>
#include <QStringList>
#include "filters.h"

class ImageManager {
private:
    cv::Mat originalImage;
    cv::Mat processedImage;
    QStringList appliedFilters;
public:
    bool loadImage(const QString& path);
    void applyFilter(const QString& filterName);
    const cv::Mat& getOriginalImage() const;
    const cv::Mat& getProcessedImage() const;
    void resetProcessedImage();
    void resetAppliedFiltersList();
    void resetOriginalImage();
    const QStringList& getFiltersList() const;
};

#endif // IMAGEMANAGER_H
