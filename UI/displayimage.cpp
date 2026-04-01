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
}

void DisplayImage::setImage(const QImage &image) {
    if(image.isNull()){
        scene->clear();
        return;
    }
    this->image = image;
    QPixmap pixmap = QPixmap::fromImage(this->image);
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
    ui->saveButton->setEnabled(permission);
}

DisplayImage::~DisplayImage() {
    delete ui;
}

void DisplayImage::callSave() {
    saveWinodw = new SaveImage(this);
    connect(saveWinodw, &SaveImage::saveConfirmed, this, [this](const QString& name) {emit saveRequest(name, this->image);});
    saveWinodw->exec();
}

void DisplayImage::callClose() {
    close();
}
