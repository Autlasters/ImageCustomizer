#include "saveimage.h"
#include "ui_saveimage.h"

SaveImage::SaveImage(const QStringList& extensions, QWidget *parent): QDialog(parent), ui(new Ui::SaveImage) {
    ui->setupUi(this);
    ui->saveButton->setEnabled(false);
    ui->extensionsList->addItems(extensions);
    connect(ui->saveButton, &QPushButton::clicked, this, &SaveImage::callSave);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SaveImage::callCancel);
    connect(ui->nameField, &QLineEdit::textChanged, this, &SaveImage::setSaveEnable);
    connect(ui->extensionsList, &QComboBox::currentIndexChanged, this, &SaveImage::setSaveEnable);
}

void SaveImage::setSaveEnable() {
    QString name = ui->nameField->text();
    int extensionIndex = ui->extensionsList->currentIndex();
    ui->saveButton->setEnabled(!name.trimmed().isEmpty() && extensionIndex != -1);
}

SaveImage::~SaveImage() {
    delete ui;
}

void SaveImage::callSave() {
    QString name = ui->nameField->text().trimmed();
    QString extension = ui->extensionsList->currentText();
    emit saveConfirmed(name, extension);
    close();
}

void SaveImage::callCancel() {
    close();
}
