#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>
#include <QImage>
#include <QStringList>

#include "saveimage.h"
#include "wheelevent.h"

namespace Ui { class DisplayImage; }

class DisplayImage : public QDialog {
    Q_OBJECT
private:
    Ui::DisplayImage *ui;
    SaveImage *saveWinodw = nullptr;
    WheelEvent *view = nullptr;
    QImage processedImage;
    QImage originalImage;
    QStringList extensions;
    bool savePermission;
public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImages(const QImage& processedImage, const QImage& originalImage);
    void displayProcessedImage();
    void displayOriginalImage();
    void setSaveEnable(bool permission);
    void setExtensions(const QStringList& extensions);
    const QStringList& getExtensions(const QStringList& extensions) const;
    ~DisplayImage();
public slots:
    void callSave();
    void callClose();
    void callProcessedImage();
    void callOriginalImage();
signals:
    void saveRequest(const QString& name, const QString& extension, const QImage& image);
    void imagesLoaded();
};

#endif // DISPLAYIMAGE_H
