#ifndef IMAGETOSIGNALMANAGER_H
#define IMAGETOSIGNALMANAGER_H

#include <opencv2/opencv.hpp>
#include <QVector>
#include <QImage>

class ImageToSignalManager {
private:
    cv::Mat originalGrayScaledImage;
    cv::Mat processedGrayScaledImage;
public:
    ImageToSignalManager();
    void setImages(const QImage& originalImage, const QImage& processedImage);
    QVector<double> getOriginalImagRowValues(const int& y) const;
    QVector<double> getprocessedImagRowValues(const int& y) const;
};

#endif // IMAGETOSIGNALMANAGER_H
