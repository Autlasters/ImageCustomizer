#include "plotwindow.h"
#include "ui_plotwindow.h"

PlotWindow::PlotWindow(QWidget *parent): QDialog(parent), ui(new Ui::PlotWindow) {
    ui->setupUi(this);
    mode = Mode::NormalCurves;
    ui->plotArea->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plotArea->yAxis->setRange(0, 255);

    ui->rowSlider->setSingleStep(1);
    ui->rowSlider->setPageStep(10);
    ui->rowSlider->setFocusPolicy(Qt::StrongFocus);
    ui->rowSlider->setTickPosition(QSlider::TicksBelow);
    ui->rowSlider->setTickInterval(50);

    setTheme();
    ui->plotArea->addGraph();
    ui->plotArea->addGraph();
    ui->plotArea->graph(0)->setName("Original Image Curve");
    ui->plotArea->graph(1)->setName("Processed Image Curve");
    ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190)));
    ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95)));
    setLegend();

    connect(ui->closeButton, &QPushButton::clicked, this, &PlotWindow::callClose);
    connect(ui->defaultCurvesButton, &QPushButton::clicked, this, &PlotWindow::callNormalCurves);
    connect(ui->differentiaCurveButton, &QPushButton::clicked, this, &PlotWindow::callDifferentialCurve);
    connect(ui->rowSlider, &QSlider::valueChanged, this, [=](int value){ui->rowNumberLabel->setText(QString::number(value));});
    connect(ui->rowSlider, &QSlider::valueChanged, this, &PlotWindow::sliderIndexChanged);
    QTimer::singleShot(0, this, [this]() {emit ui->rowSlider->valueChanged(ui->rowSlider->value());});

    ui->defaultCurvesButton->setEnabled(false);
}

PlotWindow::~PlotWindow() {
    delete ui;
}

void PlotWindow::setTheme() {
    QColor axisColor = QColor(200, 200, 200);
    QColor gridColor = QColor(80, 80, 80);

    ui->plotArea->setBackground(this->palette().window().color());

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

void PlotWindow::setLegend() {
    ui->plotArea->legend->setBrush(QBrush(this->palette().window().color()));
    ui->plotArea->legend->setBorderPen(QPen(Qt::gray));
    QFont font("Segoe UI", 10, QFont::Bold);
    ui->plotArea->legend->setFont(font);
    ui->plotArea->legend->setTextColor(Qt::white);
    ui->plotArea->legend->setIconSize(QSize(30, 20));
    ui->plotArea->legend->setRowSpacing(5);
    ui->plotArea->legend->setColumnSpacing(7);
    ui->plotArea->legend->setMargins(QMargins(8, 4, 8, 4));
    ui->plotArea->legend->setVisible(true);
}

void PlotWindow::updateLegendLayout() {
    ui->plotArea->legend->clearItems();
    for(int i = 0; i < ui->plotArea->graphCount(); ++i){
        QCPGraph *graph = ui->plotArea->graph(i);
        if(graph->visible() && !graph->name().isEmpty()){
            ui->plotArea->legend->addItem(new QCPPlottableLegendItem(ui->plotArea->legend, graph));
        }
    }
}

void PlotWindow::updateLegend() {
    if(mode == Mode::NormalCurves){
        ui->plotArea->graph(0)->setName("Original Image Curve");
        ui->plotArea->graph(1)->setName("Processed Image Curve");
        ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190)));
        ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95)));
        ui->plotArea->graph(1)->setVisible(true);
    }
    else if(mode == Mode::DifferentialCurve){
        ui->plotArea->graph(0)->setName("Differential Curve");
        ui->plotArea->graph(0)->setPen(QPen(QColor(127, 183, 126)));
        ui->plotArea->graph(1)->setVisible(false);
    }
    updateLegendLayout();
    ui->plotArea->replot();
}

void PlotWindow::setRowSlider(const int &value) {
    ui->rowSlider->setMaximum(value);
}

void PlotWindow::setHorizontalAxis(const int &xAxis) {
    ui->plotArea->xAxis->setRange(0, xAxis);
}

void PlotWindow::drawCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues) {
    int width = origianlValues.size();
    QVector<double> x(width);
    for (int i = 0; i < width; ++i) {
        x[i] = i;
    }
    if(mode == Mode::NormalCurves){
        ui->plotArea->graph(0)->setData(x, origianlValues);
        ui->plotArea->graph(1)->setData(x, processedValues);
        ui->plotArea->graph(1)->setVisible(true);
    }
    else if(mode == Mode::DifferentialCurve){
        QVector<double> y = calculateDifferentialCurve(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(x, y);
        ui->plotArea->graph(1)->setVisible(false);
    }
    ui->plotArea->replot();
}

QVector<double> PlotWindow::calculateDifferentialCurve(const QVector<double> &origianlValues, const QVector<double> &processedValues){
    QVector<double> difference(origianlValues.size());
    for(int i = 0; i < origianlValues.size(); ++i){
        difference[i] = processedValues[i] - origianlValues[i];
    }
    return difference;
}

void PlotWindow::callNormalCurves() {
    mode = Mode::NormalCurves;
    sliderIndexChanged(ui->rowSlider->value());
    updateLegend();
    ui->defaultCurvesButton->setEnabled(false);
    ui->differentiaCurveButton->setEnabled(true);
    ui->smothedCurvesButton->setEnabled(true);
}

void PlotWindow::callDifferentialCurve() {
    mode = Mode::DifferentialCurve;
    sliderIndexChanged(ui->rowSlider->value());
    updateLegend();
    ui->differentiaCurveButton->setEnabled(false);
    ui->defaultCurvesButton->setEnabled(true);
    ui->smothedCurvesButton->setEnabled(true);
}

void PlotWindow::callClose() {
    close();
}
