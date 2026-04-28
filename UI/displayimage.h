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
    PlotWindow *plotWinodw = nullptr;
    WheelEvent *view = nullptr;
    ImageToSignalManager imageToSignalManager;
    QImage processedImage;
    QImage originalImage;
    QStringList extensions;
    bool savePermission;
    bool curvesAnalysisPermission;
public:
    explicit DisplayImage(QWidget *parent = nullptr);
    void setImages(const QImage& processedImage, const QImage& originalImage);
    void setPermissons(bool savePermission, bool curvesAnalysisPermission);
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
    void valuesCalculated(const QVector<double>& origianlValues, const QVector<double>& processedValues);

};

#endif // DISPLAYIMAGE_H
