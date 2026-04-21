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
    ui->filtersList->addItems(FiltersCollector::getAllDefaultFilters());

    QString savingFolderPath = settings.value("savingFolderPath", "").toString();
    if(!savingFolderPath.isEmpty() &&  QDir(savingFolderPath).exists()){
        ui->DisplayFolderPathField->setText(savingFolderPath);
    }

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::callExit);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::callProcess);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::callClear);
    connect(ui->setFolderButton, &QPushButton::clicked, this, &MainWindow::callSearch);
    connect(ui->filtersList, &QComboBox::currentIndexChanged, this, &MainWindow::changeButtonsState);
    connect(ui->resizecheckBox, &QCheckBox::toggled, this, &MainWindow::fillFiltersDropdown);

    view = ui->dragAndDropArea;
    connect(view, &CustomView::imageDropped, this, &MainWindow::imageDropped);
    connect(view, &CustomView::imageDropped, this, &MainWindow::changeButtonsState);
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
    if(ui->resizecheckBox->isChecked()){
        imageManager.applyResizingFilter(filter);
    }
    else{
        imageManager.applyDefaultFilter(filter);
    }
    displayWindow = new DisplayImage(this);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(displayWindow, &QObject::destroyed, this, [this]() {displayWindow = nullptr;});
    connect(displayWindow, &DisplayImage::saveRequest, this, &MainWindow::saveImage);

    if(!ui->DisplayFolderPathField->text().isEmpty()){
        displayWindow->setSaveEnable(true);
    }
    displayWindow->setImages(Converter::MatToQImge(imageManager.getProcessedImage()), Converter::MatToQImge(imageManager.getOriginalImage()));
    displayWindow->setExtensions(userImageIO.getExtensions());
    displayWindow->show();
}

void MainWindow::callClear() {
    view->clearScene();
    ui->processButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    imageManager.resetOriginalImage();
    imageManager.resetProcessedImage();
    imagesLoaded = false;
}

void MainWindow::callExit() {
    close();
}

void MainWindow::imageDropped(const QString &path) {
    if(!imageManager.loadImage(path)){
        return;
    }
    imagesLoaded = true;
}

void MainWindow::saveImage(const QString &name, const QString& extension, const QImage &image) {
    if(ui->DisplayFolderPathField->text().isEmpty()){
        return;
    }
    if(!userImageIO.setFolderPath(ui->DisplayFolderPathField->text())){
        return;
    }
    cv::Mat mat = Converter::QImageToMat(image);
    userImageIO.saveImage(mat, name, extension);
}

void MainWindow::changeButtonsState() {
    ui->processButton->setEnabled(imagesLoaded && ui->filtersList->currentIndex() != -1);
    ui->clearButton->setEnabled(imagesLoaded);
}

void MainWindow::fillFiltersDropdown(bool checked) {
    ui->filtersList->clear();
    if(checked){
        ui->filtersList->addItems(FiltersCollector::getAllResizingFilters());
        ui->filtersList->setPlaceholderText("Resizing");
    }
    else{
        ui->filtersList->addItems(FiltersCollector::getAllDefaultFilters());
        ui->filtersList->setPlaceholderText("Filters");
    }
    ui->filtersList->setCurrentIndex(-1);
}


