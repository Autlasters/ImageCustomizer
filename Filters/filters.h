#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>
#include <QString>

class Filters {
public:
    virtual ~Filters();
    virtual void apply(const cv::Mat& image) = 0;
    virtual QString getFilter() const = 0;

};

class BlackAndWhiteFilter: Filters {
public:
    void apply(const cv::Mat& image) override;
    QString getFilter() const override;
};

class BlurFilter: Filters {
public:
    void apply(const cv::Mat& image) override;
    QString getFilter() const override;
};



#endif // FILTERS_H
