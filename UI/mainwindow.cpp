#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << CV_VERSION;
    qDebug() << CV_VERSION_MAJOR;
    qDebug() << CV_VERSION_MINOR;
}

MainWindow::~MainWindow()
{
    delete ui;
}
