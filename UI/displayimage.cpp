#include <QGraphicsPixmapItem>

#include "displayimage.h"
#include "ui_displayimage.h"

DisplayImage::DisplayImage(QWidget *parent): QDialog(parent), ui(new Ui::DisplayImage) {
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);

    connect(ui->saveButton, &QPushButton::clicked, this, &DisplayImage::callSave);
    connect(ui->closeButton, &QPushButton::clicked, this, &DisplayImage::callClose);
    connect(ui->displayProcessedImageButton, &QPushButton::clicked, this, &DisplayImage::callProcessedImage);
    connect(ui->displayOriginalImageButton, &QPushButton::clicked, this, &DisplayImage::callOriginalImage);
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
    emit imagesLoaded();
}

void DisplayImage::displayProcessedImage(){
    view->setImage(processedImage);
}

void DisplayImage::displayOriginalImage(){
    view->setImage(originalImage);
}

void DisplayImage::setSaveEnable(bool permission) {
    savePermission = permission;
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
    displayProcessedImage();
    ui->saveButton->setEnabled(savePermission);
    ui->displayProcessedImageButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(true);
}

void DisplayImage::callOriginalImage(){
    displayOriginalImage();
    ui->saveButton->setEnabled(false);
    ui->displayOriginalImageButton->setEnabled(false);
    ui->displayProcessedImageButton->setEnabled(true);
}

void DisplayImage::callClose() {
    close();
}

