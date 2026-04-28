#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QVector>

class PlotManager {
private:
    QVector<double> origianlValues;
    QVector<double> processedValues;
public:
    PlotManager();
    QVector<double> calculateHorizontalValues(const QVector<double>& values);
    QVector<double> calculateDifferentialCurve(const QVector<double>& originalValues, const QVector<double>& processedValues);
    QVector<double> calculateDifferentialSmoothedCurve(const QVector<double>& originalValues, const QVector<double>& processedValues);
    std::pair<QVector<double>, QVector<double>> calculateSmoothedCurves(const QVector<double>& originalValues, const QVector<double>& processedValues);
};

#endif // PLOTMANAGER_H
