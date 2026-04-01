#include "filters.h"

//Black&White Filter
void BlackAndWhiteFilter::apply(cv::Mat& image) {
    if (image.empty()){
        return;
    }
    cv::Mat result;
    cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
    cv::cvtColor(result, image, cv::COLOR_GRAY2BGR);
}

QString BlackAndWhiteFilter::getFilterName() const{
    return "BlackAndWhite";
}

//Blur Filter
void BlurFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat result;
    cv::GaussianBlur(image, result, cv::Size(5,5), 0);
    image = result;
}

QString BlurFilter::getFilterName() const{
    return "Blur";
}
