#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

#include "plotmanager.h"

namespace Ui { class PlotWindow; }

enum Mode {NormalCurves, DifferentialCurve, SmoothedCurves, DifferentialSmoothedCurve};

class PlotWindow : public QDialog {
    Q_OBJECT
private:
    Ui::PlotWindow *ui;
    PlotManager plotManager;
    Mode mode;
public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    void setTheme();
    void setLegend();
    void updateLegendLayout();
    void updateLegend();
    void setRowSliderRange(const int& value);
    void setHorizontalAxis(const int& xAxis);
public slots:
    void drawCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void changeMode(const QString &mode);
    void callClose();
signals:
    void sliderIndexChanged(const int& index);
};

#endif // PLOTWINDOW_H
