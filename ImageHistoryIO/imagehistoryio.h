#ifndef IMAGEHISTORYIO_H
#define IMAGEHISTORYIO_H

#include <QString>
#include "imagehistorymanager.h"

class ImageHistoryIO {
private:
    QString path;
public:
    bool setPath(const QString path);
    bool saveHistory(const ImageHistory& obj);
    std::vector<ImageHistory> loadHistory();
};

#endif // IMAGEHISTORYIO_H
