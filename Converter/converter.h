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
