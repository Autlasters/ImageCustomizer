/*
 * displayimage.cpp
 *
 * This source file implements the logic of the methods of the class DisplayImage
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include <QGraphicsPixmapItem>
#include "displayimage.h"
#include "ui_displayimage.h"

//Constructor
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

//Destructor
DisplayImage::~DisplayImage() {
    delete ui;
}

//Method to set the images
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

//Method to set the permission for the image saving
void DisplayImage::setPermission(bool savePermission) {
    this->savePermission = savePermission;
    ui->saveButton->setEnabled(this->savePermission);
}

//Method to set the chosen extension
void DisplayImage::setExtensions(const QStringList &extensions) {
    if(extensions.empty()){
        return;
    }
    this->extensions = extensions;
}

//Method to verify if the processed image is in grayscale format
void DisplayImage::checkProcessedImage() {
    if(processedImage.format() == QImage::Format_Grayscale8){
        plotWindow->lockRGBMode();
    }
}

//Method to call the window for the image saving
void DisplayImage::callSave() {
    saveWinodw = new SaveImage(extensions, this);
    connect(saveWinodw, &SaveImage::saveConfirmed, this, [this](const QString& name, const QString& extension) {emit saveRequest(name, extension,
                                                                                                                this->processedImage);});
    saveWinodw->exec();
}

//Method to show the processed image
void DisplayImage::callProcessedImage(){
    view->setImage(processedImage);
    ui->saveButton->setEnabled(savePermission);
    ui->displayProcessedImageButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(true);
}

//Method to show the original image
void DisplayImage::callOriginalImage(){
    view->setImage(originalImage);
    ui->saveButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(false);
    ui->displayProcessedImageButton->setEnabled(true);
}

//Method to call the curve analysis window
void DisplayImage::callCurveAnalysis() {
    plotWindow = new PlotWindow(this);
    plotWindow->setRowSliderRange(originalImage.height()-1);
    plotWindow->setHorizontalAxis(originalImage.width());
    plotWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(plotWindow, &QObject::destroyed, this, [this]() {plotWindow = nullptr;});
    connect(plotWindow, &PlotWindow::sliderIndexChanged, this, &DisplayImage::calculateValues);
    connect(this, &DisplayImage::grayScaledValuesCalculated, plotWindow, &PlotWindow::drawGrayScaledCurves);
    connect(this, &DisplayImage::rgbValuesCalculated, plotWindow, &PlotWindow::drawRBGCurves);
    checkProcessedImage();
    plotWindow->exec();
}

//Method to calculate the curves value for the curves analysis
void DisplayImage::calculateValues(const int &index){
    int mappedIndex = index;
    if(originalImage.height() != processedImage.height()){
        double scale = static_cast<double>(processedImage.height())/static_cast<double>(originalImage.height());
        mappedIndex = static_cast<int>(index*scale);
        mappedIndex = std::min(mappedIndex, processedImage.height()-1);
    }

    if(plotWindow->getMode() == "RGB mode"){
        auto [originalRed, originalGreen, originalBlue] = imageToSignalManager.getOriginalRGBImageRowValues(index);
        auto [processedRed, processedGreen, processedBlue] = imageToSignalManager.getProcessedRGBImageRowValues(mappedIndex);
        emit rgbValuesCalculated({originalRed, processedRed}, {originalGreen, processedGreen}, {originalBlue, processedBlue});
    }
    else{
        QVector<double> originalValues = imageToSignalManager.getOriginalGrayScaledImageRowValues(index);
        QVector<double> processeValues = imageToSignalManager.getProcessedGrayScaledImageRowValues(mappedIndex);
        emit grayScaledValuesCalculated(originalValues, processeValues);
    }
}

//Method to close the window
void DisplayImage::callClose() {
    close();
}


