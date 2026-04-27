#include <QGraphicsPixmapItem>

#include "displayimage.h"
#include "ui_displayimage.h"

DisplayImage::DisplayImage(QWidget *parent): QDialog(parent), ui(new Ui::DisplayImage), imageToSignalManager(ImageToSignalManager()) {
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &DisplayImage::callSave);
    connect(ui->closeButton, &QPushButton::clicked, this, &DisplayImage::callClose);
    connect(ui->displayProcessedImageButton, &QPushButton::clicked, this, &DisplayImage::callProcessedImage);
    connect(ui->displayOriginalImageButton, &QPushButton::clicked, this, &DisplayImage::callOriginalImage);
    connect(ui->curvesAnalysisButton, &QPushButton::clicked, this, &DisplayImage::callCurveAnalysis);
    connect(this, &DisplayImage::imagesLoaded, this, &DisplayImage::callProcessedImage);
    view = ui->displayArea;
}

void DisplayImage::setImages(const QImage& processedImage, const QImage& originalImage) {
    if(processedImage.isNull() || originalImage.isNull()){
        view->clearScene();
        return;
    }
    this->processedImage = processedImage;
    this->originalImage = originalImage;
    imageToSignalManager.setImages(this->originalImage, this->processedImage);
    emit imagesLoaded();
}

void DisplayImage::setPermissons(bool savePermission, bool curvesAnalysisPermission) {
    this->savePermission = savePermission;
    this->curvesAnalysisPermission = curvesAnalysisPermission;
    ui->saveButton->setEnabled(this->savePermission);
    ui->curvesAnalysisButton->setEnabled(this->curvesAnalysisPermission);
}

void DisplayImage::setExtensions(const QStringList &extensions) {
    if(extensions.empty()){
        return;
    }
    this->extensions = extensions;
}

DisplayImage::~DisplayImage() {
    delete ui;
}

void DisplayImage::callSave() {
    saveWinodw = new SaveImage(extensions, this);
    connect(saveWinodw, &SaveImage::saveConfirmed, this, [this](const QString& name, const QString& extension) {emit saveRequest(name, extension,
                                                                                                                this->processedImage);});
    saveWinodw->exec();
}

void DisplayImage::callProcessedImage(){
    view->setImage(processedImage);
    ui->saveButton->setEnabled(savePermission);
    ui->displayProcessedImageButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(true);
}

void DisplayImage::callOriginalImage(){
    view->setImage(originalImage);
    ui->saveButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(false);
    ui->displayProcessedImageButton->setEnabled(true);
}

void DisplayImage::callCurveAnalysis() {
    plotWinodw = new PlotWindow(this);
    plotWinodw->setRowSliderRange(originalImage.height()-1);
    plotWinodw->setHorizontalAxis(originalImage.width());
    plotWinodw->setAttribute(Qt::WA_DeleteOnClose);
    connect(plotWinodw, &QObject::destroyed, this, [this]() {plotWinodw = nullptr;});
    connect(plotWinodw, &PlotWindow::sliderIndexChanged, this, &DisplayImage::calculateValues);
    connect(this, &DisplayImage::valuesCalculated, plotWinodw, &PlotWindow::drawCurves);
    plotWinodw->exec();
}

void DisplayImage::calculateValues(const int &index){
    QVector<double> originalValues = imageToSignalManager.getOriginalImagRowValues(index);
    QVector<double> processeValues = imageToSignalManager.getprocessedImagRowValues(index);
    emit valuesCalculated(originalValues, processeValues);
}

void DisplayImage::callClose() {
    close();
}


