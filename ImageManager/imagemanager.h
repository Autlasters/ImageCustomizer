/*
 * imagemanager.h
 *
 * This header file represents the ImageManager class, which is responsible for interacting with the image
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

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
    void applyResizingFilter(const QString& dimension);
    void resetOriginalImage();
    void resetProcessedImage();
    const cv::Mat& getOriginalImage() const;
    const cv::Mat& getProcessedImage() const;
};

#endif // IMAGEMANAGER_H
