/*
 * mainwindow.cpp
 *
 * This source file implements the logic of the methods of the class MainWindow
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include<QFileDialog>
#include<QDir>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include "filterscollector.h"

//Constructor
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), settings("ImageCustomizer", "Settings"),
                                                                                                mode(Mode::DefaultMode) {
    ui->setupUi(this);
    ui->processButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->DisplayFolderPathField->setReadOnly(true);
    ui->DisplayFolderPathField->setPlaceholderText("Click Search to chose the folder for the images saving");
    fillFiltersDropdown();
    fillModeDropDown();

    QString savingFolderPath = settings.value("savingFolderPath", "").toString();
    if(!savingFolderPath.isEmpty() &&  QDir(savingFolderPath).exists()){
        ui->DisplayFolderPathField->setText(savingFolderPath);
    }

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::callClose);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::callProcess);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::callClear);
    connect(ui->setFolderButton, &QPushButton::clicked, this, &MainWindow::callSearch);
    connect(ui->filtersList, &QComboBox::currentIndexChanged, this, &MainWindow::changeButtonsState);
    connect(ui->modeDropdown, &QComboBox::currentIndexChanged, this, &MainWindow::changeMode);
    connect(this, &MainWindow::filtersModeChanged, this, &MainWindow::fillFiltersDropdown);

    view = ui->dragAndDropArea;
    connect(view, &CustomView::imageDropped, this, &MainWindow::imageDropped);
    connect(view, &CustomView::imageDropped, this, &MainWindow::changeButtonsState);
}

//Destructor
MainWindow::~MainWindow() {
    delete ui;
}

//Method to set the path to the saving folder
void MainWindow::callSearch() {
    QString savingFolderPath = settings.value("savingFolderPath", "C://").toString();
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Set folder"), savingFolderPath, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(!folderPath.isEmpty()){
        ui->DisplayFolderPathField->clear();
        ui->DisplayFolderPathField->setText(folderPath);
    }
    settings.setValue("savingFolderPath", folderPath);
}

//Method to process the image
void MainWindow::callProcess() {
    QString filter = ui->filtersList->currentText();
    if(filter.isEmpty()){
        return;
    }
    if(mode == Mode::ResizingMode){
        imageManager.applyResizingFilter(filter);
    }
    else{
        imageManager.applyFilter(filter);
    }
    displayWindow = new DisplayImage(this);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(displayWindow, &QObject::destroyed, this, [this]() {displayWindow = nullptr;});
    connect(displayWindow, &DisplayImage::saveRequest, this, &MainWindow::saveImage);

    bool savePermission = false;
    if(!ui->DisplayFolderPathField->text().isEmpty()){
        savePermission = true;
    }

    displayWindow->setPermission(savePermission);
    displayWindow->setImages(Converter::MatToQImge(imageManager.getProcessedImage()), Converter::MatToQImge(imageManager.getOriginalImage()));
    displayWindow->setExtensions(userImageIO.getExtensions());
    displayWindow->show();
}

//Method to clean the drag&drop field
void MainWindow::callClear() {
    view->clearScene();
    ui->processButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    imageManager.resetOriginalImage();
    imageManager.resetProcessedImage();
    imagesLoaded = false;
}

//Method to close the application
void MainWindow::callClose() {
    close();
}

//Method to load an image
void MainWindow::imageDropped(const QString &path) {
    if(!imageManager.loadImage(path)){
        return;
    }
    imagesLoaded = true;
}

//Method to save an image
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

//Method to change the buttons' state when the image is loaded into the application
void MainWindow::changeButtonsState() {
    ui->processButton->setEnabled(imagesLoaded && ui->filtersList->currentIndex() != -1);
    ui->clearButton->setEnabled(imagesLoaded);
}

//Method to fill filters dropdown dynamically
void MainWindow::fillFiltersDropdown() {
    ui->filtersList->clear();
    switch(mode){
    case Mode::DefaultMode:{
        ui->filtersList->addItems(FiltersCollector::getAllDefaultFilters());
        ui->filtersList->setPlaceholderText("Filters");
        break;
    }
    case Mode::ResizingMode:{
        ui->filtersList->addItems(FiltersCollector::getAllResizingFilters());
        ui->filtersList->setPlaceholderText("Dimensions");
        break;
    }
    case Mode::ColorSpacesMode:{
        ui->filtersList->addItems(FiltersCollector::getAllColorSpaceFilters());
        ui->filtersList->setPlaceholderText("Color Spaces");
        break;
    }
    }
    ui->filtersList->setCurrentIndex(-1);
}

//Method to fill the mode dropdown
void MainWindow::fillModeDropDown() {
    ui->modeDropdown->addItem("Filters", Mode::DefaultMode);
    ui->modeDropdown->addItem("Resizing", Mode::ResizingMode);
    ui->modeDropdown->addItem("Color Spaces", Mode::ColorSpacesMode);
}

//Method to change the mode
void MainWindow::changeMode() {
    QVariant option = ui->modeDropdown->currentData();
    mode = static_cast<Mode>(option.toInt());
    emit filtersModeChanged();
}


