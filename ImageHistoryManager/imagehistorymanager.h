#ifndef IMAGEHISTORYMANAGER_H
#define IMAGEHISTORYMANAGER_H

#include "imagehistory.h"
#include <vector>
#include <QStringList>

class ImageHistoryManager {
private:
    std::vector<ImageHistory> history;
    QStringList historyNames;
public:
    void addHistory(const QString& imagePath, const QString& imageName, const QStringList& appliedFiltersHistory);
    void removeHistory(const int& index);
    void clearHistory();
    const ImageHistory* getImageHistory(const QString& imageName) const;
    const QStringList& getHistoryNames() const;
    const std::vector<ImageHistory>& getAll() const;
};

#endif // IMAGEHISTORYMANAGER_H
