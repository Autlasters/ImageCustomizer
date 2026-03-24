#include "displayimage.h"
#include "ui_displayimage.h"
#include "saveimage.h"

DisplayImage::DisplayImage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DisplayImage)
{
    ui->setupUi(this);

    connect(ui->saveButton, &QPushButton::clicked, this, &DisplayImage::callSave);
    connect(ui->closeButton, &QPushButton::clicked, this, &DisplayImage::callClose);
}

DisplayImage::~DisplayImage()
{
    delete ui;
}

void DisplayImage::callSave() {
    SaveImage *window = new SaveImage();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void DisplayImage::callClose() {
    close();
}
