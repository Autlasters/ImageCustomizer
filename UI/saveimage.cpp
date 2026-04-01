#include "saveimage.h"
#include "ui_saveimage.h"

SaveImage::SaveImage(QWidget *parent): QDialog(parent), ui(new Ui::SaveImage) {
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);

    connect(ui->saveButton, &QPushButton::clicked, this, &SaveImage::callSave);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SaveImage::callCancel);
    connect(ui->nameField, &QLineEdit::textChanged, this, &SaveImage::setSaveEnable);
}

void SaveImage::setSaveEnable(const QString &name) {
    ui->saveButton->setEnabled(!name.trimmed().isEmpty());
}

SaveImage::~SaveImage() {
    delete ui;
}

void SaveImage::callSave() {
    QString name = ui->nameField->text().trimmed();
    emit saveConfirmed(name);
    close();
}

void SaveImage::callCancel() {
    emit saveCanceled();
    close();
}
