/*
 * plotmanager.h
 *
 * This header file represents the PlotManager class, which is responsible for calculating signal curves
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#ifndef PLOTMANAGER_H
#define PLOTMANAGER_H

#include <QVector>

class PlotManager {
private:
    QVector<double> origianlValues;
    QVector<double> processedValues;
public:
    QVector<double> calculateHorizontalValues(const QVector<double>& values);
    QVector<double> calculateDifferentialCurve(const QVector<double>& originalValues, const QVector<double>& processedValues);
    QVector<double> calculateDifferentialSmoothedCurve(const QVector<double>& originalValues, const QVector<double>& processedValues);
    std::pair<QVector<double>, QVector<double>> calculateSmoothedCurves(const QVector<double>& originalValues, const QVector<double>& processedValues);
    QVector<double> linearInterpolation(const QVector<double>& values, const int& size);
};

#endif // PLOTMANAGER_H
