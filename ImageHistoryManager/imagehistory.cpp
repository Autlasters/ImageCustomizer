#include "imagehistory.h"

ImageHistory::ImageHistory(const QString& imagePath, const QString& imageName, const QStringList& appliedFiltersHistory):
    imagePath(imagePath), imageName(imageName), appliedFiltersHistory(appliedFiltersHistory)
{}

QString ImageHistory::getImagePath() const{
    return imagePath;
}

QString ImageHistory::getImageName() const{
    return imageName;
}

const QStringList& ImageHistory::getFiltersHistory() const{
    return appliedFiltersHistory;
}
