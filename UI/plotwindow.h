#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

#include "plotmanager.h"

namespace Ui { class PlotWindow; }

class PlotWindow : public QDialog {
    Q_OBJECT
private:
    enum MainMode {DefaultMode, RGBMode};
    enum DefaultCurvesMode {NormalCurves, SmoothedCurves, DifferentialCurve, DifferentialSmoothedCurve};
    enum RGBCurvesMode {OriginalRGBCurves, ProcessedRGBCurves, OriginalSmoothedRGBCurves, ProcessedSmoothedRGBCurves,
                        NormalRedCurves, SmoothedRedCurves, DifferentialRedCurve, DifferentialSmoothedRedCurve,
                        NormalGreenCurves, SmoothedGreenCurves, DifferentialGreenCurve, DifferentialSmoothedGreenCurve,
                        NormalBlueCurves, SmoothedBlueCurves, DifferentialBlueCurve, DifferentialSmoothedBlueCurve};
    Ui::PlotWindow *ui;
    PlotManager plotManager;
    QVector<double> xAxis;
    MainMode mainMode;
    DefaultCurvesMode defaultCurvesMode;
    RGBCurvesMode rgbCurvesMode;
public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    void setTheme();
    void setLegend();
    void updateLegendLayout();
    void updateLegend();
    void setRowSliderRange(const int& value);
    void setHorizontalAxis(const int& xAxis);
    void lockRGBMode();
    QString getMode() const;
public slots:
    void drawGrayScaledCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void drawRBGCurves(const std::pair< QVector<double>&, const QVector<double>&> red,
                       const std::pair< QVector<double>&, const QVector<double>&> green,
                       const std::pair< QVector<double>&, const QVector<double>&> blue);
    void changeMainMode(bool checked);
    void changeCurvesMode();
    void fillModeDropDown();
    void takeScreenShot();
    void callClose();
signals:
    void sliderIndexChanged(const int& index);
    void mainModeChanged();
};

#endif // PLOTWINDOW_H
