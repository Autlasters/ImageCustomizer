#include "plotmanager.h"

#include <opencv2/opencv.hpp>

PlotManager::PlotManager() {}

QVector<double> PlotManager::calculateHorizontalValues(const QVector<double> &values) {
    QVector<double> xValeus(values.size());
    for (int i = 0; i < values.size(); ++i) {
        xValeus[i] = i;
    }
    return xValeus;
}

QVector<double> PlotManager::calculateDifferentialCurve(const QVector<double> &originalValues, const QVector<double> &processedValues) {
    QVector<double> differentialValues(originalValues.size());
    for(int i = 0; i <  originalValues.size(); ++i){
        differentialValues[i] = processedValues[i] -  originalValues[i];
    }
    return differentialValues;
}

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



