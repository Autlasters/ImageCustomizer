#ifndef IMAGEHISTORYIO_H
#define IMAGEHISTORYIO_H

#include <QString>
#include <fstream>
#include <sstream>
#include "imagehistorymanager.h"

class ImageHistoryIO {
private:
    QString path;
public:
    bool setPath(const QString& path);
    bool saveHistory(const std::vector<ImageHistory>& history) const;
    std::vector<ImageHistory> loadHistory() const;
};

#endif // IMAGEHISTORYIO_H
