#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <QString>

class ImageIO {
private:
    QString path;
public:
    bool setPath(const QString path);
    bool saveImage(const QString name);
    bool loadImage(const QString name);
};

#endif // IMAGEIO_H
