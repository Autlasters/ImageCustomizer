#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <opencv2/opencv.hpp>
#include <QVector>
#include <QImage>

class PlotManager {
private:
    cv::Mat originalGrayScaledImage;
    cv::Mat processedGrayScaledImage;
public:
    PlotManager();
    void setImages(const QImage& originalImage, const QImage& processedImage);
    QVector<double> getOriginalImagRowValues(const int& y) const;
    QVector<double> getprocessedImagRowValues(const int& y) const;
    const cv::Mat& getOriginalGrayScaledImage() const;
    const cv::Mat& getProcessedGrayScaledImage() const;
};

#endif // PLOTMANAGER_H
