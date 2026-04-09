#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>
#include <QImage>
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
    bool savePermission;
public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImages(const QImage& processedImage, const QImage& originalImage);
    void displayProcessedImage();
    void displayOriginalImage();
    void setSaveEnable(bool permission);
    void setScale();
    ~DisplayImage();
public slots:
    void callSave();
    void callClose();
    void callProcessedImage();
    void callOriginalImage();
signals:
    void saveRequest(const QString& name, const QImage& image);
    void imagesLoaded();
};

#endif // DISPLAYIMAGE_H
