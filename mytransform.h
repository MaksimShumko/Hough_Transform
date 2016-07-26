#ifndef MYTRANSFORM_H
#define MYTRANSFORM_H

#include "transform.h"

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class MyTransform : public Transform
{
public:
    void houghTransform(cv::Mat *dst, double *rho, double *theta,
                        int *threshold, double *srn, double *stn,
                        double *min_theta, double *max_theta);

    cv::Mat drawLines();

    void showAccum();

private:
    std::vector<cv::Vec2f> _lines;
    cv::Mat _cdst;

    unsigned int* _accu;
    int _accu_w;
    int _accu_h;
    int _img_w;
    int _img_h;
};

#endif // MYTRANSFORM_H
