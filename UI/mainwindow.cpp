#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "converter.h"

#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::callHistoryWindow);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::callExit);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::callProcess);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainWindow::callClear);
    connect(ui->setFolderButton, &QPushButton::clicked, this, &MainWindow::callSearch);

    dragAndDropField = ui->dragAndDropFiled;
    connect(dragAndDropField, &CustomView::imageDropped, this, &MainWindow::imageDropped);

    ui->filtersList->addItems({"Black and White", "Blur"});
    // histroyImageIO.setPath("Images History"); in development
    historyFileIO.setPath("history.txt");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::callSearch() {
    QString folderPath = QFileDialog::getExistingDirectory(this, tr("Set folder"), "C://", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->DisplyaFolderPathField->clear();
    ui->DisplyaFolderPathField->setText(folderPath);
}

void MainWindow::callHistoryWindow() {
    historyWindow = new HistoryWindow(this);
    historyWindow->setAttribute(Qt::WA_DeleteOnClose);
    historyWindow->setHistoryManager(&imageHistoryManager);
    connect(historyWindow, &HistoryWindow::showRequest, this, &MainWindow::showHistory);
    historyWindow->show();
}

void MainWindow::callExit() {
    close();
}

void MainWindow::callProcess() {
    QString filter = ui->filtersList->currentText();
    if(filter.isEmpty()) return;
    imageManager.applyFilter(filter);
    QImage image = Converter::MatToQImge(imageManager.getProcessedImage());
    displayWindow = new DisplayImage(this);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose);
    connect(displayWindow, &QObject::destroyed, this, [this]() {displayWindow = nullptr;});
    displayWindow->setImage(image);
    connect(displayWindow, &DisplayImage::saveRequest, this, &MainWindow::saveImage);
    displayWindow->show();
    QString name  = QString::number(QDateTime::currentSecsSinceEpoch());
    //histroyImageIO.saveImage(imageManager.getProcessedImage(), name);  in development
    imageHistoryManager.addHistory( histroyImageIO.getPathToImage(name), name, imageManager.getFiltersList());
    historyFileIO.saveHistory(imageHistoryManager.getAll());
}

void MainWindow::callClear() {
    if(scene){
        scene->clear();
    }
    ui->dragAndDropFiled->resetTransform();
    ui->dragAndDropFiled->viewport()->update();
    imageManager.resetOriginalImage();
    imageManager.resetProcessedImage();
    imageManager.resetAppliedFiltersList();
}

void MainWindow::imageDropped(const QString &path) {
    if(!imageManager.loadImage(path)) return;
    cv::Mat mat = imageManager.getProcessedImage();
    QImage image = Converter::MatToQImge(mat);
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    ui->dragAndDropFiled->setScene(scene);
}

void MainWindow::saveImage(const QString &name, const QImage &image) {
    if(ui->DisplyaFolderPathField->text().isEmpty()) return;
    if(!userImageIO.setPath(ui->DisplyaFolderPathField->text())) return;
    cv::Mat mat = Converter::QImageToMat(image);
    userImageIO.saveImage(mat, name);
}

void MainWindow::showHistory(const QString &path) {
    if(!imageManager.loadImage(path)) return;
    QImage image = Converter::MatToQImge(imageManager.getProcessedImage());
    displayWindow = new DisplayImage(this);
    displayWindow->setAttribute(Qt::WA_DeleteOnClose);
    displayWindow->setImage(image);
    connect(displayWindow, &DisplayImage::saveRequest, this, &MainWindow::saveImage);
    displayWindow->show();
}
