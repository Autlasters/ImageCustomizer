/*
 * imagemanager.cpp
 *
 * This source file implements the logic of the methods of the class ImageManager
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include <QImage>
#include "imagemanager.h"
#include "filtersfactory.h"
#include "converter.h"

//Method to load an image
bool ImageManager::loadImage(const QString& path){
    if(path.isEmpty()){
        return false;
    }

    QImage image;
    image.load(path.toUtf8());
    if(image.isNull()){
        return false;
    }

    originalImage = Converter::QImageToMat(image);

    if(originalImage.empty()){
        return false;
    }

    processedImage = originalImage.clone();
    return true;
}

//Method to apply a filter on an image
void ImageManager::applyFilter(const QString& filterName){
    std::unique_ptr<Filter> filter = FiltersFactory::createFilter(filterName);
    if(!filter){
        return;
    }

    processedImage = originalImage.clone();

    filter->apply(processedImage);
}

//Method to apply the resizing filter on an image
void ImageManager::applyResizingFilter(const QString &dimension) {
    std::unique_ptr<ResizingFilter> filter = std::make_unique<ResizingFilter>();
    if(!filter){
        return;
    }
    processedImage = originalImage.clone();
    filter->determineDimension(dimension);
    filter->apply(processedImage);
}

//Method to reset the original image
void ImageManager::resetOriginalImage() {
    if(originalImage.empty()){
        return;
    }
    originalImage.release();
}

//Method to reset the processed image
void ImageManager::resetProcessedImage(){
    if(processedImage.empty()){
        return;
    }
    if(originalImage.empty()){
        return;
    }
    processedImage = originalImage.clone();
}

//Method to get the original image
const cv::Mat& ImageManager::getOriginalImage() const {
    return originalImage;
}

//Method to get the processed image
const cv::Mat& ImageManager::getProcessedImage() const{
    return processedImage;
}

