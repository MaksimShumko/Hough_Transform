#ifndef HOUGHLINES_H
#define HOUGHLINES_H

#include <QWidget>

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

cv::Mat Hough1(cv::Mat *dst, double *rho,
               double *theta, int *threshold, double *srn, double *stn,
               double *min_theta, double *max_theta);

#endif // HOUGHLINES_H
