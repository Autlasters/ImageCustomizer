#include "imagetosignalmanager.h"
#include "converter.h"

ImageToSignalManager::ImageToSignalManager() {}

void ImageToSignalManager::setImages(const QImage &originalImage, const QImage &processedImage) {
    if(originalImage.format() != QImage::Format_Grayscale8){
        QImage grayScaledOriginal = originalImage.convertToFormat(QImage::Format_Grayscale8);
        originalGrayScaledImage = Converter::QImageToMat(grayScaledOriginal);
    }
    else{
        originalGrayScaledImage = Converter::QImageToMat(originalImage);
    }

    if(processedImage.format() != QImage::Format_Grayscale8){
        QImage grayScaledProcessed = processedImage.convertToFormat(QImage::Format_Grayscale8);
        processedGrayScaledImage = Converter::QImageToMat(grayScaledProcessed);
    }
    else{
        processedGrayScaledImage = Converter::QImageToMat(processedImage);
    }
}

QVector<double> ImageToSignalManager::getOriginalImagRowValues(const int &y) const {
    cv::Mat rowMat = originalGrayScaledImage.row(y);
    QVector<double> values;
    for(int col = 0; col < rowMat.cols; ++col){
        uchar value = rowMat.at<uchar>(0, col);
        values.append(static_cast<double>(value));
    }
    return values;
}

QVector<double> ImageToSignalManager::getprocessedImagRowValues(const int &y) const {
    cv::Mat rowMat = processedGrayScaledImage.row(y);
    QVector<double> values;
    for(int col = 0; col < rowMat.cols; ++col){
        uchar value = rowMat.at<uchar>(0, col);
        values.append(static_cast<double>(value));
    }
    return values;
}


