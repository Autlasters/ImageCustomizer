#ifndef FILTERS_H
#define FILTERS_H

#include <opencv2/opencv.hpp>
#include <QString>

//-----------------------------------------------------Abstract Filter class -----------------------------------------------------
class Filter {
public:
    virtual ~Filter() = default;
    virtual void apply(cv::Mat& image) = 0;
    virtual QString getFilterName() const = 0;
};

//-----------------------------------------------------Black&White Filter-----------------------------------------------------
class BlackAndWhiteFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Blur Filter-----------------------------------------------------
class BlurFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Bright Filter-----------------------------------------------------
class BrightFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Warm Filter-----------------------------------------------------
class WarmFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Cold Filter-----------------------------------------------------
class ColdFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Sharp Filter-----------------------------------------------------
class SharpFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Sepia Filter-----------------------------------------------------
class SepiaFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Edge Detection Filter-----------------------------------------------------
class EdgeDetectionFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Negative Filter-----------------------------------------------------
class NegativeFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

//-----------------------------------------------------Pencil Sketch Filter-----------------------------------------------------
class PencilSketchFilter: public Filter {
public:
    void apply(cv::Mat& image) override;
    QString getFilterName() const override;
};

#endif // FILTERS_H
