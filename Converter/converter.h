/*
 * converter.h
 *
 * This header file represents the Converter class, which is responsible for converting the cv::Mat variable to QImage and vice versa
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef CONVERTER_H
#define CONVERTER_H

#include <opencv2/opencv.hpp>
#include <QImage>

class Converter {
public:
    static QImage MatToQImge(const cv::Mat& image);
    static cv::Mat QImageToMat(const QImage& image);
};

#endif // CONVERTER_H
