#include "converter.h"

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
        return QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888).copy();
    }

    return QImage();
}

cv::Mat Converter::QImageToMat(const QImage& image){
    QImage qimage = image.convertToFormat(QImage::Format_RGB888);
    cv::Mat mat (qimage.height(), qimage.width(), CV_8UC3, (void*)qimage.bits(), qimage.bytesPerLine());
    cv::Mat result;
    cv::cvtColor(mat, result, cv::COLOR_RGB2BGR);
    return result.clone();
}
