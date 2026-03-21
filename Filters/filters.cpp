#include "filters.h"

void BlackAndWhiteFilter::apply(cv::Mat& image) {
    cv::Mat result;
    cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
    image = result;
}

QString BlackAndWhiteFilter::getFilterName() const{
    return "BlackAndWhite";
}


void BlurFilter::apply(cv::Mat& image){
    cv::Mat result;
    cv::GaussianBlur(image, result, cv::Size(5,5), 0);
    image = result;
}

QString BlurFilter::getFilterName() const{
    return "Blur";
}
