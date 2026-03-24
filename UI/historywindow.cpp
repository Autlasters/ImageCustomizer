#include "historywindow.h"
#include "ui_historywindow.h"
#include "displayimage.h"

HistoryWindow::HistoryWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, this, &HistoryWindow::callClose);
    connect(ui->showButton, &QPushButton::clicked, this, &HistoryWindow::callShow);
}

HistoryWindow::~HistoryWindow()
{
    delete ui;
}

void HistoryWindow::callShow() {
    DisplayImage *window = new DisplayImage();
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}

void HistoryWindow::callClose()
{
    close();
}
