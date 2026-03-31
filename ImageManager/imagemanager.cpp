#include "imagemanager.h"
#include "filtersfactory.h"
#include "converter.h"

#include <QImage>

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

    resetAppliedFiltersList();
    processedImage = originalImage.clone();
    return true;
}

void ImageManager::applyFilter(const QString& filterName){
    std::unique_ptr<Filter> filter = FiltersFactory::createFilter(filterName);
    if(!filter){
        return;
    }
    if(processedImage.empty()){
        return;
    }

    processedImage = originalImage.clone();

    filter->apply(processedImage);
    appliedFilters << filter->getFilterName();
}

const cv::Mat& ImageManager::getOriginalImage() const {
    return originalImage;
}

const cv::Mat& ImageManager::getProcessedImage() const{
    return processedImage;
}

const QStringList& ImageManager::getFiltersList() const{
    return appliedFilters;
}

void ImageManager::resetProcessedImage(){
    if(originalImage.empty()){
        return;
    }
    processedImage = originalImage.clone();
    resetAppliedFiltersList();
}

void ImageManager::resetAppliedFiltersList(){
    appliedFilters.clear();
}

void ImageManager::resetOriginalImage() {
    originalImage.release();
}

