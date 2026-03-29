#include "saveimage.h"
#include "ui_saveimage.h"

#include <QMessageBox>

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
    QString name = ui->nameField->text().trimmed();
    if(name.isEmpty()){
        QMessageBox::warning(this, "Error", "Name field can not be empty!");
        return;
    }
    emit saveConfirmed(name);
    close();
}

void SaveImage::callCancel()
{
    emit saveCanceled();
    close();
}
