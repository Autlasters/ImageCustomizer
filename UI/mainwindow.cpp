#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "displayimage.h"
#include "historywindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << CV_VERSION;
    qDebug() << CV_VERSION_MAJOR;
    qDebug() << CV_VERSION_MINOR;

    connect(ui->historyButton, &QPushButton::clicked, this, &MainWindow::callHistoryWindow);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::callExit);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::callProcess);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::callHistoryWindow() {
    HistoryWindow *window = new HistoryWindow();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();

}

void MainWindow::callExit() {
    close();
}

void MainWindow::callProcess() {
    DisplayImage *window = new DisplayImage();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}
