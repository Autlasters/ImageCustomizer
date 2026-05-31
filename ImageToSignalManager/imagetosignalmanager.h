/*
 * imagetosignalmanager.h
 *
 * This header file represents the ImageToSignalManager class, which is responsible for coverting the image in to a signal
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef IMAGETOSIGNALMANAGER_H
#define IMAGETOSIGNALMANAGER_H

#include <opencv2/opencv.hpp>
#include <QVector>
#include <QImage>
#include <tuple>

class ImageToSignalManager {
private:
    cv::Mat originalImage;
    cv::Mat processedImage;
    cv::Mat originalGrayScaledImage;
    cv::Mat processedGrayScaledImage;
public:
    void setImages(const QImage& originalImage, const QImage& processedImage);
    QVector<double> getOriginalGrayScaledImageRowValues(const int& y) const;
    QVector<double> getProcessedGrayScaledImageRowValues(const int& y) const;
    std::tuple<QVector<double>, QVector<double>, QVector<double>> getOriginalRGBImageRowValues(const int& y) const;
    std::tuple<QVector<double>, QVector<double>, QVector<double>> getProcessedRGBImageRowValues(const int& y) const;
};

#endif // IMAGETOSIGNALMANAGER_H
