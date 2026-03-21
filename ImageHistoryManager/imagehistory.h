#ifndef IMAGEHISTORY_H
#define IMAGEHISTORY_H

#include <QString>
#include <QStringList>

class ImageHistory {
private:
    QString imageName;
    QString imagePath;
    QStringList appliedFiltersHistory;
public:
    ImageHistory(const QString& imagePath, const QString& imageName, const QStringList& appliedFiltersHistory);
    QString getImagePath() const;
    QString getImageName() const;
    const QStringList& getFiltersHistory() const;
};

#endif // IMAGEHISTORY_H
