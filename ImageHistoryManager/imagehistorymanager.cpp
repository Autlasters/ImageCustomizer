#include "imagehistorymanager.h"

void ImageHistoryManager::addHistory(const QString& imagePath, const QString& imageName, const QStringList& appliedFiltersHistory){
    history.emplace_back(imagePath, imageName, appliedFiltersHistory);
    historyNames << imageName;
}

void ImageHistoryManager::removeHistory(const int& index){
    if(index >= 0 && index < history.size()){
        history.erase(history.begin() + index);
        historyNames.erase(historyNames.begin() + index);
    }
}

void ImageHistoryManager::clearHistory(){
    history.clear();
    historyNames.clear();
}

const ImageHistory* ImageHistoryManager::getImageHistory(const QString& imageName) const{
    for(const auto& obj : history){
        if(obj.getImageName() == imageName){
            return &obj;
        }
    }
    return nullptr;
}

const QStringList& ImageHistoryManager::getHistoryNames() const{
    return historyNames;
}

const std::vector<ImageHistory> &ImageHistoryManager::getAll() const {
    return history;
}
