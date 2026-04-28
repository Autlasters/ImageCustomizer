#include <QStringList>

#include "filters.h"

//-----------------------------------------------------Black&White Filter-----------------------------------------------------
void BlackAndWhiteFilter::apply(cv::Mat& image) {
    if (image.empty()){
        return;
    }
    cv::Mat result;

    //converts the image colors forom BGR(BLUE, GREEN, RED) format to GRAY one channel
    cv::cvtColor(image, result, cv::COLOR_BGR2GRAY);
    image = result;
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

    /*applys the blure effect to the image, cv::Size(5,5) - size of the Kernel matrix, 3 - Gaussian kernel standard deviation in x direction
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

    /*increases the brigtness and the contrast of the image, -1 - the desired output matrix, -1 means that output matrix will have the same type
    with the original one, 1.3 - the brigtness value alpha (a>0), 40 - the contrast value beta*/
    image.convertTo(result, -1, 1.3, 40);
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
    cv::Mat hsv;
    std::vector<cv::Mat> channels, hsvChannels;

    //creates two tables with 1 row and 256 elemets, where each element can has the value only in range [0, 255]
    cv::Mat increaseLUT(1, 256, CV_8UC1);
    cv::Mat decreaseLUT(1, 256, CV_8UC1);

    /*fills the tables with the value*multiplier, i*1.2 - increase brightness of the pixel, i*0.8 - decrease brightness of the pixel,
    cv::saturate_cast - does not allow to leave the range [0, 255]*/
    for(int i = 0; i< 256; ++i){
        increaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*1.2);
        decreaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*0.8);
    }

    //splits the matrix to three chanels BLUE, GREEN, RED (BGR)
    cv::split(image, channels);

    //decreses the BLUE channel brightness (LUT - Look Up Table)
    cv::LUT(channels[0], decreaseLUT, channels[0]);

    //increases the RED channel brightness
    cv::LUT(channels[2], increaseLUT, channels[2]);

    //Connects channel together
    cv::merge(channels, image);

    //converts the image colors forom BGR format to HSV (Hue, Saturation, Value)
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    //splits the matrix to three chanels HUE, SATURATION, VALUE (HSV)
    cv::split(hsv, hsvChannels);

    //increases the Saturation channel
    cv::LUT(channels[1], increaseLUT, channels[1]);

    //Connects channel together
    cv::merge(hsvChannels, hsv);

    //converts the image colors forom HSV format to BGR
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
    cv::Mat hsv;
    std::vector<cv::Mat> channels, hsvChannels;

    //creates two tables with 1 row and 256 elemets, where each element can has the value only in range [0, 255]
    cv::Mat increaseLUT(1, 256, CV_8UC1);
    cv::Mat decreaseLUT(1, 256, CV_8UC1);

    /*fills the tables with the value*multiplier, i*1.2 - increase brightness of the pixel, i*0.8 - decrease brightness of the pixel,
    cv::saturate_cast - does not allow to leave the range [0, 255]*/
    for(int i = 0; i< 256; ++i){
        increaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*1.2);
        decreaseLUT.at<uchar>(i) = cv::saturate_cast<uchar>(i*0.8);
    }

    //splits the matrix to three chanels BLUE, GREEN, RED (BGR)
    cv::split(image, channels);

    //decreses the BLUE channel brightness (LUT - Look Up Table)
    cv::LUT(channels[0], increaseLUT, channels[0]);

    //increases the RED channel brightness
    cv::LUT(channels[2], decreaseLUT, channels[2]);

    //Connects channel together
    cv::merge(channels, image);

    //converts the image colors forom BGR format to HSV (Hue, Saturation, Value)
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    //splits the matrix to three chanels HUE, SATURATION, VALUE (HSV)
    cv::split(hsv, hsvChannels);

    //increases the Saturation channel
    cv::LUT(channels[1], decreaseLUT, channels[1]);

    //Connects channel together
    cv::merge(hsvChannels, hsv);

    //converts the image colors forom HSV format to BGR
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

    /*convolution Kernel matrix - Preserves the center pixel with a positive weight and
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

            //compute the values of each color of the pixel (BGR order)
            uchar newBlue = cv::saturate_cast<uchar>((0.131 * pixel[0]) + (0.534 * pixel[1]) + (0.272 * pixel[2]));
            uchar newGreen = cv::saturate_cast<uchar>((0.168 * pixel[0]) +  (0.686 * pixel[1]) + (0.349 * pixel[2]));
            uchar newRed= cv::saturate_cast<uchar>((0.189 * pixel[0]) + (0.769 * pixel[1]) + (0.393 * pixel[2]));

            //replaces the colors of each pixel with computed values
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

    //converts the image colors forom BGR(BLUE, GREEN, RED) format to GRAY one channel
    cv::cvtColor(image, grayScaled, cv::COLOR_BGR2GRAY);

    cv::Mat Sobelx, Sobely, Gradient;

    /*applies Sobel operator horizontaly: CV_64F - allows negative gradient, 1 - order of the derivative in the x-direction,
    0 - order of the derivative in the y-direction 3 - size of the extended Sobel kernel*/
    cv::Sobel(grayScaled, Sobelx, CV_64F, 1, 0, 3);

    /*applies Sobel operator verticaly: CV_64F - allows negative gradient, 1 - order of the derivative in the x-direction,
    0 - order of the derivative in the y-direction 3 - size of the extended Sobel kernel*/
    cv::Sobel(grayScaled, Sobely, CV_64F, 0, 1, 3);

    //computes the gradient magnitude
    cv::magnitude(Sobelx, Sobely, Gradient);
    cv::Mat result;

    //converts the mathematical result into the suitable image form: uint8 [0-255]
    cv::convertScaleAbs(Gradient, result);

    image = result;
}

QString EdgeDetectionFilter::getFilterName() const{
    return "EdgeDetection";
}

//-----------------------------------------------------Negative Filter-----------------------------------------------------
void NegativeFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat result = image.clone();

    //the loop for accessing each pixel of the image and transforming it
    for(int y = 0; y < image.rows; ++y){
        for(int x = 0; x < image.cols; ++x){

            //access to the particular pixel
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);

            //compute the values of each color of the pixel (BGR order)
            uchar newBlue = 255 - pixel[0];
            uchar newGreen = 255 - pixel[1];
            uchar newRed = 255 - pixel[2];

            //replaces the colors of each pixel with computed values
            result.at<cv::Vec3b>(y, x) = cv::Vec3b(newBlue, newGreen, newRed);
        }
    }
    image = result;
}

QString NegativeFilter::getFilterName() const{
    return "Negative";
}

//-----------------------------------------------------Pencil Sketch Filter-----------------------------------------------------
void PencilSketchFilter::apply(cv::Mat& image){
    if (image.empty()){
        return;
    }
    cv::Mat greyImage, blurredImage, devideImage, maskedImage, result;

    //converts the image colors forom BGR(BLUE, GREEN, RED) format to GRAY one channel
    cv::cvtColor(image, greyImage, cv::COLOR_BGR2GRAY);

    /*applys the blure effect to the image, cv::Size(15,15) - size of the Kernel matrix, 0, 0 - Gaussian kernel standard deviation
    in x and y directions for the bigger coeffitients, the stronger the blur effect*/
    cv::GaussianBlur(greyImage, blurredImage, cv::Size(15, 15), 0, 0);

    //makes bright areasof the image white, dark areas and edges stay dark.  256 - scale coefficient
    cv::divide(greyImage, blurredImage, devideImage, 256);

    /*removes weak details from the image and enhance the sketch contrast. 70 - thresh value, 255 - maximum value of the thresholding type,
    THRESH_BINARY - thresholding type*/
    cv::threshold(devideImage, maskedImage, 70, 255, cv::THRESH_BINARY);

    //combines threshold mask - maskedImage, with the original sketch - devideImage
    cv::bitwise_and(maskedImage, devideImage, result);
    image = result;
}

QString PencilSketchFilter::getFilterName() const{
    return "Pencil Sketch";
}

//-----------------------------------------------------Resizing Filter-----------------------------------------------------
void ResizingFilter::determineDimension(const QString &dimension) {
    if(dimension.isEmpty()){
        return;
    }
    QStringList widthAndHeight = dimension.split('x');
    if(widthAndHeight.size() == 2){
        width = widthAndHeight[0].toInt();
        height = widthAndHeight[1].toInt();
    }
}

void ResizingFilter::apply(cv::Mat &image) {
    if (image.empty()){
        return;
    }
    cv::Mat result;

    /*resizes the image to the particular dimension, cv::Size(width, height) - the dimension of the new image, 0, 0 - the scaling factor, can be
    used instead of cv::Size(width, height), cv::INTER_LINEAR - the type of calculations of the pixel values in the new image*/
    cv::resize(image, result, cv::Size(width, height), 0, 0, cv::INTER_LINEAR);
    image = result;
}

QString ResizingFilter::getFilterName() const {
    return "Resizing Filter";
}


