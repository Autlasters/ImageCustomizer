/*
 * converter.cpp
 *
 * This source file implements the logic of the methods for the class Converter
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include "converter.h"

//Method to convert the variable of the type cv::Mat to QImage
QImage Converter::MatToQImge(const cv::Mat& image){
    if(image.empty()){
        return QImage();
    }
    if(image.type() == CV_8UC3){
        cv::Mat temp;
        cv::cvtColor(image, temp, cv::COLOR_BGR2RGB);
        return QImage(temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888).copy();
    }
    if(image.type() == CV_8UC1){
        return QImage(image.data, image.cols, image.rows, image.step, QImage::Format_Grayscale8).copy();
    }
    return QImage();
}

//Method to convert the variable of the type QImage to cv::Mat
cv::Mat Converter::QImageToMat(const QImage& image){
    if(image.isNull()){
        return cv::Mat();
    }
    QImage converted = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat temp(converted.height(), converted.width(), CV_8UC3, (void*)converted.bits(), converted.bytesPerLine());
    cv::Mat result;
    cv::cvtColor(temp, result, cv::COLOR_RGB2BGR);
    return result.clone();
}
