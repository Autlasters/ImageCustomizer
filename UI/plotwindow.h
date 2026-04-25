#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QDialog>

namespace Ui { class PlotWindow; }

class PlotWindow : public QDialog {
    Q_OBJECT
private:
    Ui::PlotWindow *ui;
public:
    explicit PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();
    void setTheme();
    void setLegend();
    void setRowSlider(const int& value);
    void setHorizontalAxis(const int& xAxis);
public slots:
    void drawCurves(const QVector<double>& origianlValues, const QVector<double>& processedValues);
    void callClose();
signals:
    void sliderIndexChanged(const int& index);
};

#endif // PLOTWINDOW_H
