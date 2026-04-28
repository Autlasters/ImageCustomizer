#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <opencv2/opencv.hpp>

PlotWindow::PlotWindow(QWidget *parent): QDialog(parent), ui(new Ui::PlotWindow), plotManager(PlotManager()),
                                                                            mainMode(MainMode::DefaultMode),
                                                                            defaultCurvesMode(DefaultCurvesMode::NormalCurves),
                                                                            rgbCurvesMode(RGBCurvesMode::NormalRBGCurves) {
    ui->setupUi(this);
    ui->plotArea->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->plotArea->yAxis->setRange(0, 255);

    ui->rowSlider->setSingleStep(1);
    ui->rowSlider->setPageStep(10);
    ui->rowSlider->setFocusPolicy(Qt::StrongFocus);
    ui->rowSlider->setTickPosition(QSlider::TicksBelow);
    ui->rowSlider->setTickInterval(50);

    fillModeDropDown();

    setTheme();
    ui->plotArea->addGraph();
    ui->plotArea->addGraph();

    ui->plotArea->graph(0)->setName("Original Image Curve");
    ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190)));
    ui->plotArea->graph(1)->setName("Processed Image Curve");
    ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95)));

    setLegend();
    updateLegendLayout();

    connect(ui->closeButton, &QPushButton::clicked, this, &PlotWindow::callClose);
    connect(ui->rgbModeCheckBox, &QCheckBox::toggled, this, &PlotWindow::changeMainMode);
    connect(ui->modeDropDown, &QComboBox::currentTextChanged, this, &PlotWindow::changeCurvesMode);
    connect(this, &PlotWindow::mainModeChanged, this, &PlotWindow::fillModeDropDown);
    connect(ui->rowSlider, &QSlider::valueChanged, this, [=](int value){ui->rowNumberLabel->setText(QString::number(value));});
    connect(ui->rowSlider, &QSlider::valueChanged, this, &PlotWindow::sliderIndexChanged);
    QTimer::singleShot(0, this, [this]() {emit ui->rowSlider->valueChanged(ui->rowSlider->value());});
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
    if(defaultCurvesMode == DefaultCurvesMode::NormalCurves || defaultCurvesMode == DefaultCurvesMode::SmoothedCurves){
        ui->plotArea->graph(0)->setName("Original Image Curve");
        ui->plotArea->graph(1)->setName("Processed Image Curve");
        ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190)));
        ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95)));
        ui->plotArea->graph(1)->setVisible(true);
    }
    else if(defaultCurvesMode == DefaultCurvesMode::DifferentialCurve || defaultCurvesMode == DefaultCurvesMode::DifferentialSmoothedCurve){
        ui->plotArea->graph(0)->setName("Differential Curve");
        ui->plotArea->graph(0)->setPen(QPen(QColor(127, 183, 126)));
        ui->plotArea->graph(1)->setVisible(false);
    }
    updateLegendLayout();
    ui->plotArea->replot();
}

void PlotWindow::setRowSliderRange(const int &value) {
    ui->rowSlider->setMaximum(value);
}

void PlotWindow::setHorizontalAxis(const int &xAxis) {
    ui->plotArea->xAxis->setRange(0, xAxis);
}

void PlotWindow::lockRGBMode() {
    ui->rgbModeCheckBox->setEnabled(false);
}

QString PlotWindow::getMode() const {
    QString mode;
    if(mainMode == MainMode::DefaultMode){
        mode = "Default Mode";
    }
    else{
        mode = "RGB mode";
    }
    return mode;
}

void PlotWindow::drawCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues) {
    xAxis = plotManager.calculateHorizontalValues(origianlValues);
    if(defaultCurvesMode == DefaultCurvesMode::NormalCurves){
        ui->plotArea->graph(0)->setData(xAxis, origianlValues);
        ui->plotArea->graph(1)->setData(xAxis, processedValues);
        ui->plotArea->graph(1)->setVisible(true);
    }
    else if(defaultCurvesMode == DefaultCurvesMode::DifferentialCurve){
        QVector<double> y = plotManager.calculateDifferentialCurve(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
    }
    else if(defaultCurvesMode == DefaultCurvesMode::SmoothedCurves){
        auto [origianlValuesSmoothed, processedValuesSmoothed] = plotManager.calculateSmoothedCurves(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, origianlValuesSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedValuesSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
    }
    else if(defaultCurvesMode == DefaultCurvesMode::DifferentialSmoothedCurve){
        QVector<double> y = plotManager.calculateDifferentialSmoothedCurve(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
    }
    ui->plotArea->replot();
}

void PlotWindow::changeMainMode(bool checked) {
    if(checked == true){
        mainMode = MainMode::RGBMode;
    }
    else{
        mainMode = MainMode::DefaultMode;
    }
    emit mainModeChanged();
}

void PlotWindow::changeCurvesMode(const QString &mode) {
    if(mode == "Default Curves"){
        defaultCurvesMode = DefaultCurvesMode::NormalCurves;
        sliderIndexChanged(ui->rowSlider->value());
        updateLegend();
    }
    else if(mode == "Smothed Curves"){
        defaultCurvesMode = DefaultCurvesMode::SmoothedCurves;
        sliderIndexChanged(ui->rowSlider->value());
        updateLegend();
    }
    else if(mode == "Differental Curve"){
        defaultCurvesMode = DefaultCurvesMode::DifferentialCurve;
        sliderIndexChanged(ui->rowSlider->value());
        updateLegend();
    }
    else if(mode == "Smoothed Differental Curve"){
        defaultCurvesMode = DefaultCurvesMode::DifferentialSmoothedCurve;
        sliderIndexChanged(ui->rowSlider->value());
        updateLegend();
    }
}

void PlotWindow::fillModeDropDown() {
    ui->modeDropDown->clear();
    if(mainMode == MainMode::RGBMode){
        ui->modeDropDown->addItems({"Normal RGB Curves", "Smoothed RGB Curves", "Differential RGB Curves", "Differential Smoothed RGB Curves",
                                    "Normal Red Curves", "Smoothed Red Curves", "Differential Red Curve", "Differential Smoothed Red Curve",
                                    "Normal Green Curves", "Smoothed Green Curves", "Differential Green Curve", "Differential Smoothed Green Curve",
                                    "Normal Blue Curves", "Smoothed Blue Curves", "Differential Blue Curve", "Differential Smoothed Blue Curve"});
    }
    else{
        ui->modeDropDown->addItems({"Default Curves", "Smothed Curves", "Differental Curve", "Smoothed Differental Curve"});
    }
}

void PlotWindow::callClose() {
    close();
}
