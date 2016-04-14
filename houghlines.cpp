#include "houghlines.h"
#include "Canny.h"
#include "mattoqimage.h"
#include "mainwindow.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "vector"
#include "iostream"

cv::Mat Hough1(cv::Mat *dst, double *rho, double *theta,
               int *threshold, double *srn, double *stn,
               double *min_theta, double *max_theta)
{
    cv::Mat cdst;

    cv::cvtColor(*dst, cdst, cv::COLOR_GRAY2BGR);                  //Canny Edge Detector

    std::vector<cv::Vec2f> lines;

    cv::HoughLines(*dst, lines, *rho, *theta,                       //Hough Line Transform
                   *threshold, *srn, *stn,
                   *min_theta, *max_theta);

    for (size_t i = 0; i < lines.size(); i++)                       //Drawing the lines
    {
        float rho = lines[i][0], theta1 = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta1), b = sin(theta1);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        cv::line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 0.1, CV_AA);
    }

    return cdst;
}
