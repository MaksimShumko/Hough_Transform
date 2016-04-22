#ifndef HOUGHLINES_H
#define HOUGHLINES_H

#include <QWidget>

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>


class HoughLines
{
public:
    std::vector<cv::Vec2f>
    houghTransformOpenCV(cv::Mat *dst, double *rho,
                         double *theta, int *threshold,
                         double *srn, double *stn,
                         double *min_theta, double *max_theta);

    std::vector<cv::Vec2f>
    houghTransform(cv::Mat *dst, double *rho,
                   double *theta, int *threshold,
                   double *srn, double *stn,
                   double *min_theta, double *max_theta);
    void showAccum();
    cv::Mat drawLines(std::vector<cv::Vec2f> lines);
    cv::Mat drawLinesOpenCV(std::vector<cv::Vec2f> lines);

private:
    cv::Mat _cdst;

    unsigned int* _accu;
    int _accu_w;
    int _accu_h;
    int _img_w;
    int _img_h;
};

#endif // HOUGHLINES_H
