#include "saveimage.h"
#include "ui_saveimage.h"

SaveImage::SaveImage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SaveImage)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &SaveImage::callSave);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SaveImage::callCancel);
}

SaveImage::~SaveImage()
{
    delete ui;
}

void SaveImage::callSave() {
    //.......
    close();
}

void SaveImage::callCancel()
{
    close();
}
