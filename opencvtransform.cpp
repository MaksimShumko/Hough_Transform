#include "opencvtransform.h"

#include "canny.h"
#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "vector"
#include "iostream"

void OpenCVTransform::houghTransform(cv::Mat *dst, double *rho, double *theta,
                    int *threshold, double *srn, double *stn,
                    double *min_theta, double *max_theta)
{
    cv::cvtColor(*dst, _cdst, cv::COLOR_GRAY2BGR);

    std::vector<cv::Vec2f> lines;

    //Hough Line Transform
    cv::HoughLines(*dst, lines, *rho, *theta,
                   *threshold, *srn, *stn,
                   *min_theta, *max_theta);
    _lines = lines;
}

cv::Mat OpenCVTransform::drawLines()
{
    for (size_t i = 0; i < _lines.size(); i++)
    {
        float rho = _lines[i][0], theta1 = _lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta1), b = sin(theta1);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        //Drawing the lines
        cv::line(_cdst, pt1, pt2, cv::Scalar(0, 0, 255), 0.1, CV_AA);
    }
    return _cdst;
}

void OpenCVTransform::showAccum()
{

}
