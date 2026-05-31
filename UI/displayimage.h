/*
 * displayimage.h
 *
 * This header file represents the DisplayImage class, which is responsible for showing the images after processing
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef DISPLAYIMAGE_H
#define DISPLAYIMAGE_H

#include <QDialog>
#include <QImage>
#include <QStringList>
#include "saveimage.h"
#include "wheelevent.h"
#include "plotwindow.h"
#include "imagetosignalmanager.h"

namespace Ui { class DisplayImage; }

class DisplayImage : public QDialog {
    Q_OBJECT
private:
    Ui::DisplayImage *ui;
    SaveImage *saveWinodw = nullptr;
    PlotWindow *plotWindow = nullptr;
    WheelEvent *view = nullptr;
    ImageToSignalManager imageToSignalManager;
    QImage processedImage;
    QImage originalImage;
    QStringList extensions;
    bool savePermission;
public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImages(const QImage& processedImage, const QImage& originalImage);
    void setPermission(bool savePermission);
    void setExtensions(const QStringList& extensions);
    const QStringList& getExtensions(const QStringList& extensions) const;
    void checkProcessedImage();
    ~DisplayImage();
public slots:
    void callSave();
    void callClose();
    void callProcessedImage();
    void callOriginalImage();
    void callCurveAnalysis();
    void calculateValues(const int& index);
signals:
    void saveRequest(const QString& name, const QString& extension, const QImage& image);
    void imagesLoaded();
    void grayScaledValuesCalculated(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void rgbValuesCalculated(const std::pair< QVector<double>&, const QVector<double>&> red,
                             const std::pair< QVector<double>&, const QVector<double>&> green,
                             const std::pair< QVector<double>&, const QVector<double>&> blue);

};

#endif // DISPLAYIMAGE_H
