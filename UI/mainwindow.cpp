#include<QFileDialog>
#include<QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include "filterscollector.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), settings("ImageCustomizer", "Settings") {
    ui->setupUi(this);
    ui->processButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->DisplayFolderPathField->setReadOnly(true);
    ui->DisplayFolderPathField->setPlaceholderText("Click Search to chose the folder for the images saving");
    ui->filtersList->addItems(FiltersCollector::getAllFilters());

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::callExit);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::callProcess);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::callClear);
    connect(ui->setFolderButton, &QPushButton::clicked, this, &MainWindow::callSearch);

    QString savingFolderPath = settings.value("savingFolderPath", "").toString();
    if(!savingFolderPath.isEmpty() &&  QDir(savingFolderPath).exists()){
        ui->DisplayFolderPathField->setText(savingFolderPath);
    }

    view = ui->dragAndDropArea;
    connect(ui->dragAndDropArea, &CustomView::imageDropped, this, &MainWindow::checkDragAndDrop);
    connect(view, &CustomView::imageDropped, this, &MainWindow::imageDropped);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::callSearch() {
    QString savingFolderPath = settings.value("savingFolderPath", "C://").toString();
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Set folder"), savingFolderPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!folderPath.isEmpty()){
        ui->DisplayFolderPathField->clear();
        ui->DisplayFolderPathField->setText(folderPath);
    }
    settings.setValue("savingFolderPath", folderPath);
}

void MainWindow::callProcess() {
    QString filter = ui->filtersList->currentText();
    if(filter.isEmpty()){
        return;
    }
    imageManager.applyFilter(filter);
    QImage processedImg = Converter::MatToQImge(imageManager.getProcessedImage());
    QImage originalImg = Converter::MatToQImge(imageManager.getOriginalImage());
    displayWindow = new DisplayImage(this);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(displayWindow, &QObject::destroyed, this, [this]() {displayWindow = nullptr;});
    if(!ui->DisplayFolderPathField->text().isEmpty()){
        displayWindow->setSaveEnable(true);
    }
    displayWindow->setImages(processedImg, originalImg);
    connect(displayWindow, &DisplayImage::saveRequest, this, &MainWindow::saveImage);
    displayWindow->show();
}

void MainWindow::callClear() {
    view->clearScene();
    ui->processButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    imageManager.resetOriginalImage();
    imageManager.resetProcessedImage();
    imageManager.resetAppliedFiltersList();
}

void MainWindow::callExit() {
    close();
}

void MainWindow::imageDropped(const QString &path) {
    if(!imageManager.loadImage(path)){
        return;
    }
}

void MainWindow::saveImage(const QString &name, const QImage &image) {
    if(ui->DisplayFolderPathField->text().isEmpty()) return;
    if(!userImageIO.setfolderPath(ui->DisplayFolderPathField->text())) return;
    cv::Mat mat = Converter::QImageToMat(image);
    userImageIO.saveImage(mat, name);
}

void MainWindow::checkDragAndDrop(const QString &path) {
    if(!path.isEmpty()){
        ui->processButton->setEnabled(true);
        ui->clearButton->setEnabled(true);
    }
}

