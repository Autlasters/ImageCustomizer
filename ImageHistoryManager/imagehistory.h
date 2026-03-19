#ifndef IMAGEHISTORY_H
#define IMAGEHISTORY_H

#include <QString>
#include <vector>

class ImageHistory {
private:
    QString imageName;
    QString imagePath;
    std::vector<QString> filters;
public:
    ImageHistory(const QString& imagePath, const QString& name);
    void addFilter(const QString& filter);
    void clearFilters();
    QString getImagePath() const;
    QString getImageName() const;
    std::vector<QString> getFilters() const;
};

#endif // IMAGEHISTORY_H
