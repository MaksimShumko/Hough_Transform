#ifndef TRANSFORM_H
#define TRANSFORM_H

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class Transform {
public:
    virtual void houghTransform(cv::Mat *dst, double *rho, double *theta,
                                int *threshold, double *srn, double *stn,
                                double *min_theta, double *max_theta) = 0;
    virtual cv::Mat drawLines() = 0;
    virtual void showAccum() = 0;
};

#endif // TRANSFORM_H
