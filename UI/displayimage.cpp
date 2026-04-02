#include <QGraphicsPixmapItem>

#include "displayimage.h"
#include "ui_displayimage.h"

DisplayImage::DisplayImage(QWidget *parent): QDialog(parent), ui(new Ui::DisplayImage), scene(new QGraphicsScene(this)) {
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->saveButton->setEnabled(false);
    ui->graphicsView->setAlignment(Qt::AlignCenter);

    connect(ui->saveButton, &QPushButton::clicked, this, &DisplayImage::callSave);
    connect(ui->closeButton, &QPushButton::clicked, this, &DisplayImage::callClose);
    connect(ui->displayProcessedImageButton, &QPushButton::clicked, this, &DisplayImage::callProcessedImage);
    connect(ui->displayOriginalImageButton, &QPushButton::clicked, this, &DisplayImage::callOriginalImage);
    connect(this, &DisplayImage::imagesLoaded, this, &DisplayImage::callProcessedImage);
}

void DisplayImage::setImages(const QImage& processedImage, const QImage& originalImage) {
    if(processedImage.isNull() || originalImage.isNull()){
        scene->clear();
        return;
    }
    this->processedImage = processedImage;
    this->originalImage = originalImage;
    emit imagesLoaded();
}

void DisplayImage::displayProcessedImage(){
    QPixmap pixmap = QPixmap::fromImage(processedImage);
    scene->clear();
    pixmapItem = scene->addPixmap(pixmap);
    scene->setSceneRect(pixmapItem->boundingRect());
    ui->graphicsView->setScene(scene);
}

void DisplayImage::displayOriginalImage(){
    QPixmap pixmap = QPixmap::fromImage(originalImage);
    scene->clear();
    pixmapItem = scene->addPixmap(pixmap);
    scene->setSceneRect(pixmapItem->boundingRect());
    ui->graphicsView->setScene(scene);
}


void DisplayImage::resizeEvent(QResizeEvent *event) {
    QDialog::resizeEvent(event);
    if (pixmapItem) {
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
}

void DisplayImage::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    if (pixmapItem) {
        ui->graphicsView->fitInView(pixmapItem, Qt::KeepAspectRatio);
    }
}

void DisplayImage::setSaveEnable(bool permission) {
    savePermission = permission;
}

DisplayImage::~DisplayImage() {
    delete ui;
}

void DisplayImage::callSave() {
    saveWinodw = new SaveImage(this);
    connect(saveWinodw, &SaveImage::saveConfirmed, this, [this](const QString& name) {emit saveRequest(name, this->processedImage);});
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
