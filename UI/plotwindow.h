#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

namespace Ui { class PlotWindow; }

enum Mode {NormalCurves, DifferentialCurve, SmoothedCurves};

class PlotWindow : public QDialog {
    Q_OBJECT
private:
    Ui::PlotWindow *ui;
    Mode mode;
public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    void setTheme();
    void setLegend();
    void updateLegendLayout();
    void updateLegend();
    void setRowSlider(const int& value);
    void setHorizontalAxis(const int& xAxis);
    QVector<double> calculateDifferentialCurve(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    std::pair<QVector<double>, QVector<double>> calculateSmoothedCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
public slots:
    void drawCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void callNormalCurves();
    void callDifferentialCurve();
    void callClose();
signals:
    void sliderIndexChanged(const int& index);
};

#endif // PLOTWINDOW_H
