/*
 * plotmanager.cpp
 *
 * This source file implements the logic of the methods of the class PlotManager
 *
 * Built with C++ in Qt Creator using MSVC 2022 and QMake
 *
 */

#include <opencv2/opencv.hpp>
#include "plotmanager.h"

//Method to calculate the x axis values of the plotting area
QVector<double> PlotManager::calculateHorizontalValues(const QVector<double> &values) {
    QVector<double> xValeus(values.size());
    for (int i = 0; i < values.size(); ++i) {
        xValeus[i] = i;
    }
    return xValeus;
}

//Method to calculate the differential curve
QVector<double> PlotManager::calculateDifferentialCurve(const QVector<double> &originalValues, const QVector<double> &processedValues) {
    QVector<double> differentialValues(originalValues.size());
    for(int i = 0; i <  originalValues.size(); ++i){
        differentialValues[i] = processedValues[i] -  originalValues[i];
    }
    return differentialValues;
}

//Method to calculate the differential smoothed curve
QVector<double> PlotManager::calculateDifferentialSmoothedCurve(const QVector<double> &originalValues, const QVector<double> &processedValues) {
    QVector<double> differentialValues(originalValues.size());
    cv::Mat differentialValuesMat(1, originalValues.size(), CV_64F);
    for(int i = 0; i < originalValues.size(); ++i){
        differentialValuesMat.at<double>(0, i) = processedValues[i] -  originalValues[i];
    }

    cv::Mat differentialValuesMatSmoothed;
    cv::GaussianBlur(differentialValuesMat, differentialValuesMatSmoothed, cv::Size(5, 1), 3);

    for(int i = 0; i < originalValues.size(); ++i){
       differentialValues[i] = differentialValuesMatSmoothed.at<double>(0, i);
    }
    return differentialValues;
}

//Method to calculate the smoothed curves
std::pair<QVector<double>, QVector<double> > PlotManager::calculateSmoothedCurves(const QVector<double> &originalValues,
                                                                                   const QVector<double> &processedValues) {
    cv::Mat originalValuesMat(1, originalValues.size(), CV_64F);
    cv::Mat processedValuesMat(1, processedValues.size(), CV_64F);
    for(int i = 0; i < originalValues.size(); ++i){
        originalValuesMat.at<double>(0, i) = originalValues[i];
        processedValuesMat.at<double>(0, i) = processedValues[i];
    }

    cv::Mat originalValuesMatSmoothed, processedValuesMatSmoothed;
    cv::GaussianBlur(originalValuesMat, originalValuesMatSmoothed, cv::Size(5, 1), 3);
    cv::GaussianBlur(processedValuesMat, processedValuesMatSmoothed, cv::Size(5, 1), 3);

    QVector<double> originalValuesSmoothed(originalValues.size()), processedValuesSmoothed(processedValues.size());
    for(int i = 0; i < originalValues.size(); ++i){
        originalValuesSmoothed[i] = originalValuesMatSmoothed.at<double>(0, i);
        processedValuesSmoothed[i] = processedValuesMatSmoothed.at<double>(0, i);
    }
    return {originalValuesSmoothed, processedValuesSmoothed};
}

//Method to calculate the linear interpolation
QVector<double> PlotManager::linearInterpolation(const QVector<double>& values, const int &size) {
    QVector<double> result(size);
    int inputSize = values.size();
    for (int i = 0; i < size; ++i) {
        double ratio = (double)i / (size - 1);
        double position = ratio * (inputSize - 1);
        int left = floor(position);
        int right = ceil(position);
        double t = position - left;
        result[i] = (1 - t) * values[left] + t * values[right];
    }
    return result;
}



