#include "filters.h"

//-----------------------------------------------------Black&White Filter-----------------------------------------------------
void BlackAndWhiteFilter::apply(cv::Mat& image) {
    if (image.empty()){
        return;
    }
    cv::Mat result;

    //convert the image colors forom BGR(BLUE, GREEN, RED) format to GRAY one channel
    cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
    //convert the image colors forom GRAY one channel format to BGR 3-channels
    cv::cvtColor(result, image, cv::COLOR_GRAY2BGR);
}

QString BlackAndWhiteFilter::getFilterName() const{
    return "BlackAndWhite";
}

//-----------------------------------------------------Blur Filter-----------------------------------------------------
void BlurFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat result;
    /*apply the blure effect to the image, cv::Size(5,5) - size of the Karnel matrix, 3 - gaussian kernel standard deviation in x direction
    for the bigger coeffitient, the stronger the blur effect*/
    cv::GaussianBlur(image, result, cv::Size(5,5), 3);

    image = result;
}

QString BlurFilter::getFilterName() const{
    return "Blur";
}

//-----------------------------------------------------Bright Filter-----------------------------------------------------
void BrightFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat result;
    double alpha = 1.3;
    int beta = 40;
    image.convertTo(result, -1, alpha, beta);
    image = result;
}

QString BrightFilter::getFilterName() const{
    return "Bright";
}

//-----------------------------------------------------Warm Filter-----------------------------------------------------
void WarmFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }

    //create two tables with 1 row and 256 elemets, where each element can has the value only in range [0, 255]
    cv::Mat increaseLUT(1, 256, CV_8UC1);
    cv::Mat decreaseLUT(1, 256, CV_8UC1);

    /*fills the tables with the value*multiplier, i*1.2 - increase brightness of the pixel, i*0.8 - decrease brightness of the pixel,
    cv::saturate_cast - does not allow to leave the range [0, 255]*/
    for(int i = 0; i< 256; ++i){
        increaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*1.2);
        decreaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*0.8);
    }

    std::vector<cv::Mat> channels;

    //splits the matrix to three chanels BLUE, GREEN, RED (BGR)
    cv::split(image, channels);

    //decrese the BLUE channel brightness (LUT - Look Up Table)
    cv::LUT(channels[0], decreaseLUT, channels[0]);

    //increase the RED channel brightness
    cv::LUT(channels[2], increaseLUT, channels[2]);

    //Connect channel together
    cv::merge(channels, image);

    cv::Mat hsv;

    //convert the image colors forom BGR format to HSV (Hue, Saturation, Value)
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> hsvChannels;

    //splits the matrix to three chanels HUE, SATURATION, VALUE (HSV)
    cv::split(hsv, hsvChannels);

    //increase the Saturation channel
    cv::LUT(channels[1], increaseLUT, channels[1]);

    //Connect channel together
    cv::merge(hsvChannels, hsv);

    //convert the image colors forom HSV format to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

QString WarmFilter::getFilterName() const{
    return "Warm";
}

//-----------------------------------------------------Cold Filter-----------------------------------------------------
void ColdFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }

    //create two tables with 1 row and 256 elemets, where each element can has the value only in range [0, 255]
    cv::Mat increaseLUT(1, 256, CV_8UC1);
    cv::Mat decreaseLUT(1, 256, CV_8UC1);

    /*fills the tables with the value*multiplier, i*1.2 - increase brightness of the pixel, i*0.8 - decrease brightness of the pixel,
    cv::saturate_cast - does not allow to leave the range [0, 255]*/
    for(int i = 0; i< 256; ++i){
        increaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*1.2);
        decreaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*0.8);
    }

    std::vector<cv::Mat> channels;

    //splits the matrix to three chanels BLUE, GREEN, RED (BGR)
    cv::split(image, channels);

    //decrese the BLUE channel brightness (LUT - Look Up Table)
    cv::LUT(channels[0], increaseLUT, channels[0]);

    //increase the RED channel brightness
    cv::LUT(channels[2], decreaseLUT, channels[2]);

    //Connect channel together
    cv::merge(channels, image);

    cv::Mat hsv;

    //convert the image colors forom BGR format to HSV (Hue, Saturation, Value)
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> hsvChannels;

    //splits the matrix to three chanels HUE, SATURATION, VALUE (HSV)
    cv::split(hsv, hsvChannels);

    //increase the Saturation channel
    cv::LUT(channels[1], decreaseLUT, channels[1]);

    //Connect channel together
    cv::merge(hsvChannels, hsv);

    //convert the image colors forom HSV format to BGR
    cv::cvtColor(hsv, image, cv::COLOR_HSV2BGR);
}

QString ColdFilter::getFilterName() const{
    return "Cold";
}

//-----------------------------------------------------Sharp Filter-----------------------------------------------------
void SharpFilter::apply(cv::Mat& image){
    if(image.empty()){
        return;
    }
    cv::Mat result;

    /*convolution kernel matrix - Preserves the center pixel with a positive weight and
    subtracts the influence of the surrounding pixels using negative weights.*/
    cv::Mat kernel = (cv::Mat_<float>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    /*creates the sharp effect on the image, -1 - desired depth of the output image,
    cv::Point(-1, -1) - position of the anchor point within the kernel, 0 - optional value added to each pixel after filtering
    cv::BORDER_DEFAULT - pixel extrapolation method at the border*/
    cv::filter2D(image, result, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    image = result;
}

QString SharpFilter::getFilterName() const{
    return "Sharp";
}

//-----------------------------------------------------Sepia Filter-----------------------------------------------------
void SepiaFilter::apply(cv::Mat& image){
    if(image.empty()){
        return;
    }
    cv::Mat result = image.clone();

    //the loop for accessing each pixel of the image and transforming it
    for(int y = 0; y < image.rows; ++y){
        for(int x = 0; x < image.cols; ++x){

            //access to the particular pixel
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            //access to each color of the pixel (BGR order)
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];

            //transform each color
            uchar newBlue = cv::saturate_cast<uchar>((0.131 * blue) + (0.534 * green) + (0.272 * red));
            uchar newGreen = cv::saturate_cast<uchar>((0.168 * blue) +  (0.686 * green) + (0.349 * red));
            uchar newRed= cv::saturate_cast<uchar>((0.189 * blue) + (0.769 * green) + (0.393 * red));

            //replacing the colors of each pixel with computed values
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(newBlue, newGreen, newRed);
        }
    }
    image = result;
}

QString SepiaFilter::getFilterName() const{
    return "Sepia";
}

//-----------------------------------------------------Edge Detection Filter-----------------------------------------------------
void EdgeDetectionFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat grayScaled;

    //convert the image colors forom BGR(BLUE, GREEN, RED) format to GRAY one channel
    cv::cvtColor(image, grayScaled, cv::COLOR_BGR2GRAY);

    cv::Mat Sobelx, Sobely, Gradient;

    /*applies Sobel operator horizontaly: CV_64F - allows negative gradient, 1 - order of the derivative in the x-direction,
    0 - order of the derivative in the y-direction 3 - size of the extended Sobel kernel*/
    cv::Sobel(grayScaled, Sobelx, CV_64F, 1, 0, 3);

    /*applies Sobel operator verticaly: CV_64F - allows negative gradient, 1 - order of the derivative in the x-direction,
    0 - order of the derivative in the y-direction 3 - size of the extended Sobel kernel*/
    cv::Sobel(grayScaled, Sobely, CV_64F, 0, 1, 3);

    //compute the gradient magnitude
    cv::magnitude(Sobelx, Sobely, Gradient);
    cv::Mat result;

    //convert the mathematical result into the suitable image form: uint8 [0-255]
    cv::convertScaleAbs(Gradient, result);

    //convert the image colors forom GRAY one channel format to BGR 3-channels
    cv::cvtColor(result, result, cv::COLOR_GRAY2BGR);
    image = result;
}

QString EdgeDetectionFilter::getFilterName() const{
    return "EdgeDetection";
}
