#ifndef IMAGEHISTORYMANAGER_H
#define IMAGEHISTORYMANAGER_H

#include "imagehistory.h"

class ImageHistoryManager {
private:
    std::vector<ImageHistory> history;
public:
    void addHistory(const ImageHistory& obj);
    void removeHistory(const QString& objName);
    void clearHistory();

    ImageHistory* getImageHistory(const QString& objName) const;
    std::vector<QString> getHistoryNames();
};

#endif // IMAGEHISTORYMANAGER_H
