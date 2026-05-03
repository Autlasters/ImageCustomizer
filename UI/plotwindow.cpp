#include "plotwindow.h"
#include "ui_plotwindow.h"
#include <opencv2/opencv.hpp>

PlotWindow::PlotWindow(QWidget *parent): QDialog(parent), ui(new Ui::PlotWindow), plotManager(PlotManager()), mainMode(MainMode::DefaultMode),
                                                                                defaultCurvesMode(DefaultCurvesMode::NormalCurves),
                                                                                rgbCurvesMode(RGBCurvesMode::OriginalRGBCurves) {
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
    ui->plotArea->addGraph();

    ui->plotArea->graph(0)->setName("Original Image Curve");
    ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190), 0, Qt::SolidLine));
    ui->plotArea->graph(1)->setName("Processed Image Curve");
    ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95), 0, Qt::SolidLine));
    ui->plotArea->graph(2)->setVisible(false);

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
    if(mainMode == MainMode::DefaultMode) {
        if(defaultCurvesMode == DefaultCurvesMode::NormalCurves || defaultCurvesMode == DefaultCurvesMode::SmoothedCurves){
            ui->plotArea->graph(0)->setName("Original Image Curve");
            ui->plotArea->graph(1)->setName("Processed Image Curve");

            ui->plotArea->graph(0)->setPen(QPen(QColor(79, 191, 190)));
            ui->plotArea->graph(1)->setPen(QPen(QColor(224, 122, 95), 0, Qt::SolidLine));

            ui->plotArea->graph(1)->setVisible(true);
            ui->plotArea->graph(2)->setVisible(false);
        }
        if(defaultCurvesMode == DefaultCurvesMode::DifferentialCurve || defaultCurvesMode == DefaultCurvesMode::DifferentialSmoothedCurve) {
            ui->plotArea->graph(0)->setName("Differential Curve");
            ui->plotArea->graph(0)->setPen(QPen(QColor(127, 183, 126)));

            ui->plotArea->graph(1)->setVisible(false);
            ui->plotArea->graph(2)->setVisible(false);
        }
    }
    else {
        if(rgbCurvesMode == RGBCurvesMode::OriginalRGBCurves || rgbCurvesMode == RGBCurvesMode::ProcessedRGBCurves ||
            rgbCurvesMode == RGBCurvesMode::OriginalSmoothedRGBCurves || rgbCurvesMode == RGBCurvesMode::ProcessedSmoothedRGBCurves) {
            ui->plotArea->graph(0)->setName("Red Curve");
            ui->plotArea->graph(1)->setName("Green Curve");
            ui->plotArea->graph(2)->setName("Blue Curve");

            ui->plotArea->graph(0)->setPen(QPen(QColor(214, 102, 102)));
            ui->plotArea->graph(1)->setPen(QPen(QColor(102, 179, 140), 0, Qt::SolidLine));
            ui->plotArea->graph(2)->setPen(QPen(QColor(100, 149, 237)));

            ui->plotArea->graph(0)->setVisible(true);
            ui->plotArea->graph(1)->setVisible(true);
            ui->plotArea->graph(2)->setVisible(true);
        }

        else if(rgbCurvesMode == RGBCurvesMode::NormalRedCurves || rgbCurvesMode == RGBCurvesMode::SmoothedRedCurves){
            ui->plotArea->graph(0)->setName("Original Red Curves");
            ui->plotArea->graph(1)->setName("Processed Red Curves");

            ui->plotArea->graph(0)->setPen(QPen(QColor(214, 102, 102)));
            ui->plotArea->graph(1)->setPen(QPen(QColor(170, 70, 70), 0, Qt::DashLine));

            ui->plotArea->graph(1)->setVisible(true);
            ui->plotArea->graph(2)->setVisible(false);
        }
        else if(rgbCurvesMode == RGBCurvesMode::DifferentialRedCurve || rgbCurvesMode == RGBCurvesMode::DifferentialSmoothedRedCurve){
            ui->plotArea->graph(0)->setName("Differential Red Curve");

            ui->plotArea->graph(0)->setPen(QPen(QColor(214, 102, 102)));

            ui->plotArea->graph(1)->setVisible(false);
            ui->plotArea->graph(2)->setVisible(false);
        }

        else if(rgbCurvesMode == RGBCurvesMode::NormalGreenCurves || rgbCurvesMode == RGBCurvesMode::SmoothedGreenCurves){
            ui->plotArea->graph(0)->setName("Original Green Curves");
            ui->plotArea->graph(1)->setName("Processed Green Curves");

            ui->plotArea->graph(0)->setPen(QPen(QColor(102, 179, 140)));
            ui->plotArea->graph(1)->setPen(QPen(QColor(70, 140, 110), 0, Qt::DashLine));

            ui->plotArea->graph(1)->setVisible(true);
            ui->plotArea->graph(2)->setVisible(false);
        }
        else if(rgbCurvesMode == RGBCurvesMode::DifferentialGreenCurve || rgbCurvesMode == RGBCurvesMode::DifferentialSmoothedGreenCurve){
            ui->plotArea->graph(0)->setName("Differential Green Curve");

            ui->plotArea->graph(0)->setPen(QPen(QColor(102, 179, 140)));

            ui->plotArea->graph(1)->setVisible(false);
            ui->plotArea->graph(2)->setVisible(false);
        }

        else if(rgbCurvesMode == RGBCurvesMode::NormalBlueCurves || rgbCurvesMode == RGBCurvesMode::SmoothedBlueCurves){
            ui->plotArea->graph(0)->setName("Original Blue Curves");
            ui->plotArea->graph(1)->setName("Processed Blue Curves");

            ui->plotArea->graph(0)->setPen(QPen(QColor(100, 149, 237)));
            ui->plotArea->graph(1)->setPen(QPen(QColor(65, 105, 200), 0, Qt::DashLine));

            ui->plotArea->graph(1)->setVisible(true);
            ui->plotArea->graph(2)->setVisible(false);
        }
        else if(rgbCurvesMode == RGBCurvesMode::DifferentialBlueCurve || rgbCurvesMode == RGBCurvesMode::DifferentialSmoothedBlueCurve){
            ui->plotArea->graph(0)->setName("Differential Blue Curve");

            ui->plotArea->graph(0)->setPen(QPen(QColor(100, 149, 237)));

            ui->plotArea->graph(1)->setVisible(false);
            ui->plotArea->graph(2)->setVisible(false);
        }
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



void PlotWindow::drawGrayScaledCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues) {
    xAxis = plotManager.calculateHorizontalValues(origianlValues);
    /*QVector<double> processedValuesToPlot = processedValues;
    if(origianlValues.size() != processedValues.size()){
        processedValuesToPlot = plotManager.linearInterpolation(processedValues, origianlValues.size());
    }*/
    switch(defaultCurvesMode){
    case DefaultCurvesMode::NormalCurves:{
        ui->plotArea->graph(0)->setData(xAxis, origianlValues);
        ui->plotArea->graph(1)->setData(xAxis, processedValues);
        ui->plotArea->graph(1)->setVisible(true);
        break;
    }
    case DefaultCurvesMode::DifferentialCurve:{
        QVector<double> y = plotManager.calculateDifferentialCurve(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        break;
    }
    case DefaultCurvesMode::SmoothedCurves:{
        auto [origianlValuesSmoothed, processedValuesSmoothed] = plotManager.calculateSmoothedCurves(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, origianlValuesSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedValuesSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        break;
    }
    case DefaultCurvesMode::DifferentialSmoothedCurve:{
        QVector<double> y = plotManager.calculateDifferentialSmoothedCurve(origianlValues, processedValues);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        break;
    }
    }
    ui->plotArea->replot();
}

void PlotWindow::drawRBGCurves(const std::pair<QVector<double> &, const QVector<double> &> red,
                               const std::pair<QVector<double> &, const QVector<double> &> green,
                               const std::pair<QVector<double> &, const QVector<double> &> blue){

    /*auto interpolation = [&](const QVector<double>& values, const int& size){
        return (values.size() != size) ? plotManager.linearInterpolation(values, size) : values;
    };*/

    auto [originalRed, processedRed] = red;
    auto [originalGreen, processedGreen] = green;
    auto [originalBlue, processedBlue] = blue;

    /*QVector<double> processedRedToPlot = interpolation(processedRed, originalRed.size());
    QVector<double> processedGreenToPlot = interpolation(processedGreen, originalGreen.size());
    QVector<double> processedBlueToPlot = interpolation(processedBlue, originalBlue.size());*/

    auto [originalRedSmoothed, processedRedSmoothed] = plotManager.calculateSmoothedCurves(originalRed, processedRed);
    auto [originalGreenSmoothed, processedGreenSmoothed] = plotManager.calculateSmoothedCurves(originalGreen, processedGreen);
    auto [originalBlueSmoothed, processedBlueSmoothed] = plotManager.calculateSmoothedCurves(originalBlue, processedBlue);

    xAxis = plotManager.calculateHorizontalValues(originalRed);
    switch(rgbCurvesMode){
    //All Curves
    case RGBCurvesMode::OriginalRGBCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalRed);
        ui->plotArea->graph(1)->setData(xAxis, originalGreen);
        ui->plotArea->graph(2)->setData(xAxis, originalBlue);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(true);
        break;
    }
    case RGBCurvesMode::ProcessedRGBCurves:{
        ui->plotArea->graph(0)->setData(xAxis, processedRed);
        ui->plotArea->graph(1)->setData(xAxis, processedGreen);
        ui->plotArea->graph(2)->setData(xAxis, processedBlue);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(true);
        break;
    }
    case RGBCurvesMode::OriginalSmoothedRGBCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalRedSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, originalGreenSmoothed);
        ui->plotArea->graph(2)->setData(xAxis, originalBlueSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(true);
        break;
    }
    case RGBCurvesMode::ProcessedSmoothedRGBCurves:{
        ui->plotArea->graph(0)->setData(xAxis, processedRedSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedGreenSmoothed);
        ui->plotArea->graph(2)->setData(xAxis, processedBlueSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(true);
        break;
    }

    //Red Curves
    case RGBCurvesMode::NormalRedCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalRed);
        ui->plotArea->graph(1)->setData(xAxis, processedRed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::SmoothedRedCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalRedSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedRedSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialRedCurve:{
        QVector<double> y = plotManager.calculateDifferentialCurve(originalRed, processedRed);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialSmoothedRedCurve:{
        QVector<double> y = plotManager.calculateDifferentialSmoothedCurve(originalRed, processedRed);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }

    //Green Curves
    case RGBCurvesMode::NormalGreenCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalGreen);
        ui->plotArea->graph(1)->setData(xAxis, processedGreen);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::SmoothedGreenCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalGreenSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedGreenSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialGreenCurve:{
        QVector<double> y = plotManager.calculateDifferentialCurve(originalGreen, processedGreen);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialSmoothedGreenCurve:{
        QVector<double> y = plotManager.calculateDifferentialSmoothedCurve(originalGreen, processedGreen);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }

    //Blue Curves
    case RGBCurvesMode::NormalBlueCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalBlue);
        ui->plotArea->graph(1)->setData(xAxis, processedBlue);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::SmoothedBlueCurves:{
        ui->plotArea->graph(0)->setData(xAxis, originalBlueSmoothed);
        ui->plotArea->graph(1)->setData(xAxis, processedBlueSmoothed);
        ui->plotArea->graph(1)->setVisible(true);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialBlueCurve:{
        QVector<double> y = plotManager.calculateDifferentialCurve(originalBlue, processedBlue);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
    case RGBCurvesMode::DifferentialSmoothedBlueCurve:{
        QVector<double> y = plotManager.calculateDifferentialSmoothedCurve(originalBlue, processedBlue);
        ui->plotArea->graph(0)->setData(xAxis, y);
        ui->plotArea->graph(1)->setVisible(false);
        ui->plotArea->graph(2)->setVisible(false);
        break;
    }
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

void PlotWindow::changeCurvesMode() {
    QVariant option = ui->modeDropDown->currentData();
    if(mainMode == MainMode::DefaultMode){
        defaultCurvesMode = static_cast<DefaultCurvesMode>(option.toInt());
    }
    else{
        rgbCurvesMode = static_cast<RGBCurvesMode>(option.toInt());
    }
    sliderIndexChanged(ui->rowSlider->value());
    updateLegend();
}

void PlotWindow::fillModeDropDown() {
    ui->modeDropDown->clear();
    if(mainMode == MainMode::RGBMode){
        ui->modeDropDown->addItem("Original RGB Curves", RGBCurvesMode::OriginalRGBCurves);
        ui->modeDropDown->addItem("Processed RGB Curves", RGBCurvesMode::ProcessedRGBCurves);
        ui->modeDropDown->addItem("Original Smoothed RGB Curves", RGBCurvesMode::OriginalSmoothedRGBCurves);
        ui->modeDropDown->addItem("Processed Smoothed RGB Curves", RGBCurvesMode::ProcessedSmoothedRGBCurves);

        ui->modeDropDown->addItem("Normal Red Curves", RGBCurvesMode::NormalRedCurves);
        ui->modeDropDown->addItem("Smoothed Red Curves", RGBCurvesMode::SmoothedRedCurves);
        ui->modeDropDown->addItem("Differential Red Curve", RGBCurvesMode::DifferentialRedCurve);
        ui->modeDropDown->addItem("Differential Smoothed Red Curve", RGBCurvesMode::DifferentialSmoothedRedCurve);

        ui->modeDropDown->addItem("Normal Green Curves", RGBCurvesMode::NormalGreenCurves);
        ui->modeDropDown->addItem("Smoothed Green Curves", RGBCurvesMode::SmoothedGreenCurves);
        ui->modeDropDown->addItem("Differential Green Curve", RGBCurvesMode::DifferentialGreenCurve);
        ui->modeDropDown->addItem("Differential Smoothed Green Curve", RGBCurvesMode::DifferentialSmoothedGreenCurve);

        ui->modeDropDown->addItem("Normal Blue Curves", RGBCurvesMode::NormalBlueCurves);
        ui->modeDropDown->addItem("Smoothed Blue Curves", RGBCurvesMode::SmoothedBlueCurves);
        ui->modeDropDown->addItem("Differential Blue Curve", RGBCurvesMode::DifferentialBlueCurve);
        ui->modeDropDown->addItem("Differential Smoothed Blue Curve", RGBCurvesMode::DifferentialSmoothedBlueCurve);
    }
    else{
        ui->modeDropDown->addItem("Default Curves", DefaultCurvesMode::NormalCurves);
        ui->modeDropDown->addItem("Smothed Curves", DefaultCurvesMode::SmoothedCurves);
        ui->modeDropDown->addItem("Differental Curve", DefaultCurvesMode::DifferentialCurve);
        ui->modeDropDown->addItem("Smoothed Differental Curve", DefaultCurvesMode::DifferentialSmoothedCurve);
    }
}

void PlotWindow::callClose() {
    close();
}
