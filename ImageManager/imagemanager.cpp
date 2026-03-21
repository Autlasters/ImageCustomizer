#include "imagemanager.h"
#include "filtersfactory.h"

bool ImageManager::loadImage(const QString& path){
    if(path.isEmpty()){
        return false;
    }

    originalImage = cv::imread(path.toStdString());
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
        return ;
    }
    if(processedImage.empty()){
        return;
    }

    filter->apply(processedImage);
    appliedFilters << filter->getFilterName();
}

const cv::Mat& ImageManager::getOriginalImage() const {
    return originalImage;
}

const cv::Mat& ImageManager::getProcessedImage() const{
    return processedImage;
}

void ImageManager::resetProcessedImage(){
    if(originalImage.empty()){
        return;
    }
    processedImage = originalImage.clone();
    resetAppliedFiltersList();
}

const QStringList& ImageManager::getFiltersList() const{
    return appliedFilters;
}

void ImageManager::resetAppliedFiltersList(){
    appliedFilters.clear();
}

