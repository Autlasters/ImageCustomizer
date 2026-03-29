#include "historywindow.h"
#include "ui_historywindow.h"

HistoryWindow::HistoryWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HistoryWindow)
{
    ui->setupUi(this);
    connect(ui->closeButton, &QPushButton::clicked, this, &HistoryWindow::callClose);
    connect(ui->showButton, &QPushButton::clicked, this, &HistoryWindow::callShow);
    connect(ui->imageList, &QComboBox::currentTextChanged, this, &HistoryWindow::loadFilters);
}

void HistoryWindow::setHistoryManager(const ImageHistoryManager *historyManager) {
    this->historyManager = historyManager;
    ui->imageList->clear();
    if(!historyManager) return;
    ui->imageList->addItems(historyManager->getHistoryNames());
    loadFilters();
}


HistoryWindow::~HistoryWindow()
{
    delete ui;
}

void HistoryWindow::callShow() {
    if(!historyManager) return;
    const ImageHistory *obj = historyManager->getImageHistory(ui->imageList->currentText());
    if(!obj) return;
    emit showRequest(obj->getImagePath());
}

void HistoryWindow::callClose()
{
    close();
}

void HistoryWindow::loadFilters() {
    if(!historyManager) return;
    const ImageHistory *obj = historyManager->getImageHistory(ui->imageList->currentText());
    if(!obj) return;
    ui->filtersList->clear();
    ui->filtersList->addItems(obj->getFiltersHistory());
}
