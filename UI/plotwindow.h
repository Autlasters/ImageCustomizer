#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

#include "plotmanager.h"

namespace Ui { class PlotWindow; }

class PlotWindow : public QDialog {
    Q_OBJECT
public:
    enum MainMode {DefaultMode, RGBMode};
    enum DefaultCurvesMode {NormalCurves, SmoothedCurves, DifferentialCurve, DifferentialSmoothedCurve};

    enum RGBCurvesMode {OriginalRGBCurves, ProcessedRGBCurves, OriginalSmoothedRGBCurves, ProcessedSmoothedRGBCurves,
                        NormalRedCurves, SmoothedRedCurves, DifferentialRedCurve, DifferentialSmoothedRedCurve,
                        NormalGreenCurves, SmoothedGreenCurves, DifferentialGreenCurve, DifferentialSmoothedGreenCurve,
                        NormalBlueCurves, SmoothedBlueCurves, DifferentialBlueCurve, DifferentialSmoothedBlueCurve};
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
private:
    Ui::PlotWindow *ui;
    PlotManager plotManager;
    QVector<double> xAxis;
    MainMode mainMode;
    DefaultCurvesMode defaultCurvesMode;
    RGBCurvesMode rgbCurvesMode;
public slots:
    void drawGrayScaledCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void drawRBGCurves(const std::pair< QVector<double>&, const QVector<double>&> red,
                       const std::pair< QVector<double>&, const QVector<double>&> green,
                       const std::pair< QVector<double>&, const QVector<double>&> blue);
    void changeMainMode(bool checked);
    void changeCurvesMode(const QString &mode);
    void fillModeDropDown();
    void callClose();
signals:
    void sliderIndexChanged(const int& index);
    void mainModeChanged();
};

#endif // PLOTWINDOW_H
