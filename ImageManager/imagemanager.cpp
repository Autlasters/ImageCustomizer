#include <QImage>

#include "imagemanager.h"
#include "filtersfactory.h"
#include "converter.h"

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

void ImageManager::applyDefaultFilter(const QString& filterName){
    std::unique_ptr<Filter> filter = FiltersFactory::createFilter(filterName);
    if(!filter){
        return;
    }

    processedImage = originalImage.clone();

    filter->apply(processedImage);
}

void ImageManager::applyResizingFilter(const QString &dimension) {
    std::unique_ptr<ResizingFilter> filter = std::make_unique<ResizingFilter>();
    if(!filter){
        return;
    }
    processedImage = originalImage.clone();
    filter->determineDimension(dimension);
    filter->apply(processedImage);
}

void ImageManager::resetOriginalImage() {
    if(originalImage.empty()){
        return;
    }
    originalImage.release();
}

void ImageManager::resetProcessedImage(){
    if(processedImage.empty()){
        return;
    }
    if(originalImage.empty()){
        return;
    }
    processedImage = originalImage.clone();
}

const cv::Mat& ImageManager::getOriginalImage() const {
    return originalImage;
}

const cv::Mat& ImageManager::getProcessedImage() const{
    return processedImage;
}

