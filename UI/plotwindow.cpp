#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent): QDialog(parent), ui(new Ui::PlotWindow) {
    ui->setupUi(this);
    ui->plotArea->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plotArea->xAxis->setRange(0, 1000);
    ui->plotArea->yAxis->setRange(0, 255);

    setTheme();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}

void PlotWindow::setTheme() {
    QColor background = this->palette().window().color();
    QColor axisColor = QColor(200, 200, 200);
    QColor gridColor = QColor(80, 80, 80);

    ui->plotArea->setBackground(background);

    ui->plotArea->xAxis->setBasePen(QPen(axisColor));
    ui->plotArea->yAxis->setBasePen(QPen(axisColor));

    ui->plotArea->xAxis->setTickPen(QPen(axisColor));
    ui->plotArea->yAxis->setTickPen(QPen(axisColor));

    ui->plotArea->xAxis->setSubTickPen(QPen(axisColor));
    ui->plotArea->yAxis->setSubTickPen(QPen(axisColor));

    ui->plotArea->xAxis->setTickLabelColor(axisColor);
    ui->plotArea->yAxis->setTickLabelColor(axisColor);

    ui->plotArea->xAxis->grid()->setPen(QPen(gridColor, 1, Qt::DashLine));
    ui->plotArea->yAxis->grid()->setPen(QPen(gridColor, 1, Qt::DashLine));

}
