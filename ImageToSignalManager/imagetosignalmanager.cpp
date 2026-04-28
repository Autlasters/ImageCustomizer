#include "imagetosignalmanager.h"
#include "converter.h"

ImageToSignalManager::ImageToSignalManager() {}

void ImageToSignalManager::setImages(const QImage &originalImage, const QImage &processedImage) {
    if(originalImage.isNull() || processedImage.isNull()){
        return;
    }
    this->originalImage = Converter::QImageToMat(originalImage);
    this->processedImage = Converter::QImageToMat(processedImage);

    if(originalImage.format() != QImage::Format_Grayscale8){
        QImage grayScaledOriginal = originalImage.convertToFormat(QImage::Format_Grayscale8);
        this->originalGrayScaledImage = Converter::QImageToMat(grayScaledOriginal);
    }
    else{
        this->originalGrayScaledImage = Converter::QImageToMat(originalImage);
    }

    if(processedImage.format() != QImage::Format_Grayscale8){
        QImage grayScaledProcessed = processedImage.convertToFormat(QImage::Format_Grayscale8);
        this->processedGrayScaledImage = Converter::QImageToMat(grayScaledProcessed);
    }
    else{
        this->processedGrayScaledImage = Converter::QImageToMat(processedImage);
    }
}

QVector<double> ImageToSignalManager::getOriginalGrayScaledImageRowValues(const int &y) const {
    cv::Mat rowMat = originalGrayScaledImage.row(y);
    QVector<double> values;
    for(int col = 0; col < rowMat.cols; ++col){
        uchar value = rowMat.at<uchar>(0, col);
        values.append(static_cast<double>(value));
    }
    return values;
}

QVector<double> ImageToSignalManager::getProcessedGrayScaledImageRowValues(const int &y) const {
    cv::Mat rowMat = processedGrayScaledImage.row(y);
    QVector<double> values;
    for(int col = 0; col < rowMat.cols; ++col){
        uchar value = rowMat.at<uchar>(0, col);
        values.append(static_cast<double>(value));
    }
    return values;
}

std::tuple<QVector<double>, QVector<double>, QVector<double> > ImageToSignalManager::getOriginalRGBImageRowValues(const int &y) const {
    QVector<double> blue, green, red;
    cv::Mat rowMat = originalImage.row(y);
    for(int x = 0; x < rowMat.cols; ++x){
        cv::Vec3b pixel = rowMat.at<cv::Vec3b>(0, x);
        blue.append(pixel[0]);
        green.append(pixel[1]);
        red.append(pixel[2]);
    }
    return {red, green, blue};
}

std::tuple<QVector<double>, QVector<double>, QVector<double> > ImageToSignalManager::getProcessedRGBImageRowValues(const int &y) const {
    QVector<double> blue, green, red;
    cv::Mat rowMat = processedImage.row(y);
    for(int x = 0; x < rowMat.cols; ++x){
        cv::Vec3b pixel = rowMat.at<cv::Vec3b>(0, x);
        blue.append(pixel[0]);
        green.append(pixel[1]);
        red.append(pixel[2]);
    }
    return {red, green, blue};
}


