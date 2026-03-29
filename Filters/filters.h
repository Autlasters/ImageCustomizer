#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>
#include <QString>

class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(cv::Mat& image) = 0;
    virtual QString getFilterName() const = 0;
};

class BlackAndWhiteFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

class BlurFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};



#endif // FILTERS_H
