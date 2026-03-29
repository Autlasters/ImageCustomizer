#include "imagemanager.h"
#include "filtersfactory.h"

#include <QFile>
#include <QByteArray>

#include <QDebug>

bool ImageManager::loadImage(const QString& path){
    if(path.isEmpty()){
        return false;
    }

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << "Cannot open file:" << path;
        return false;
    }

    QByteArray data = file.readAll();

    std::vector<uchar> buffer(data.begin(), data.end());

    originalImage = cv::imdecode(buffer, cv::IMREAD_COLOR);

    if(originalImage.empty()){
        qDebug() << "imdecode failed";
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

