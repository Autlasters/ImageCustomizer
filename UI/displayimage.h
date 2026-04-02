#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>
#include <QImage>
#include <QGraphicsScene>

#include "saveimage.h"

namespace Ui { class DisplayImage; }

class DisplayImage : public QDialog {
    Q_OBJECT
private:
    Ui::DisplayImage *ui;
    SaveImage *saveWinodw = nullptr;
    QImage processedImage;
    QImage originalImage;
    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *pixmapItem = nullptr;
    bool savePermission;
public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImages(const QImage& processedImage, const QImage& originalImage);
    void displayProcessedImage();
    void displayOriginalImage();
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent *event);
    void setSaveEnable(bool permission);
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
