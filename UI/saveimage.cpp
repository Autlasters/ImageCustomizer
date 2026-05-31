/*
 * plotwindow.cpp
 *
 * This source file implements the logic of the methods of the class SaveImage
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include "saveimage.h"
#include "ui_saveimage.h"

//Constructor
SaveImage::SaveImage(const QStringList& extensions, QWidget *parent): QDialog(parent), ui(new Ui::SaveImage) {
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);
    ui->extensionsList->addItems(extensions);
    connect(ui->saveButton, &QPushButton::clicked, this, &SaveImage::callSave);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SaveImage::callCancel);
    connect(ui->nameField, &QLineEdit::textChanged, this, &SaveImage::setSaveEnable);
    connect(ui->extensionsList, &QComboBox::currentIndexChanged, this, &SaveImage::setSaveEnable);
}

//Destructor
SaveImage::~SaveImage() {
    delete ui;
}

//Method to allow saving an image
void SaveImage::setSaveEnable() {
    QString name = ui->nameField->text();
    int extensionIndex = ui->extensionsList->currentIndex();
    ui->saveButton->setEnabled(!name.trimmed().isEmpty() && extensionIndex != -1);
}

//Method to save an image
void SaveImage::callSave() {
    QString name = ui->nameField->text().trimmed();
    QString extension = ui->extensionsList->currentText();
    emit saveConfirmed(name, extension);
    close();
}

//Method to cancel the image saving
void SaveImage::callCancel() {
    close();
}
