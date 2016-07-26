#ifndef OPENCVTRANSFORM_H
#define OPENCVTRANSFORM_H

#include "transform.h"

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class OpenCVTransform : public Transform
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
};

#endif // OPENCVTRANSFORM_H
