#include "houghlines.h"
#include "canny.h"
#include "mattoqimage.h"
#include "mainwindow.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include "vector"
#include "iostream"

////////////////////////////////////////////////// OpenCV Hough Transform
std::vector<cv::Vec2f>
HoughLines::houghTransformOpenCV(cv::Mat *dst, double *rho, double *theta,
                                 int *threshold, double *srn, double *stn,
                                 double *min_theta, double *max_theta)
{
    cv::cvtColor(*dst, _cdst, cv::COLOR_GRAY2BGR);

    std::vector<cv::Vec2f> lines;

    //Hough Line Transform
    cv::HoughLines(*dst, lines, *rho, *theta,
                   *threshold, *srn, *stn,
                   *min_theta, *max_theta);
    return lines;
}

///////////////////////////////////////////////// My Hough Transform
std::vector<cv::Vec2f>
HoughLines::houghTransform(cv::Mat *dst, double *rho, double *theta,
                           int *threshold, double *srn, double *stn,
                           double *min_theta, double *max_theta)
{
    double radian = CV_PI/180;
    int degrees = floor((*theta) * 180/CV_PI + 0.5);

    int w = dst->cols;
    int h = dst->rows;

    unsigned char *img_data = dst->data;

    _img_w = w;                         //Number of columns
    _img_h = h;                         //Number of lines

    //Create the accumulator
    double hough_h = ((sqrt(2.0) * (double)(h > w ? h : w)) / 2.0);
    _accu_h = hough_h * 2.0; // -r -> +r
    _accu_w = 180;

    _accu = new unsigned int [_accu_h * _accu_w];
    for (int i = 0; i < _accu_h * _accu_w; i++)
    {
        _accu[i] = 0;
    }

    double center_x = w / 2;
    double center_y = h / 2;


    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (img_data[(y * w) + x] > 250)
            {
                for (int t = 0; t < 180; t = t + degrees)
                {
                    // y = x * cos( theta ) + y * sin( theta )
                    double r = (((double)x - center_x) * cos((double)t * radian)) +
                            (((double)y - center_y) * sin((double)t * radian));
                    _accu[(int)((floor(r + hough_h) * 180.0)) + t]++;
                }
            }
        }
    }

    cv::cvtColor(*dst, _cdst, cv::COLOR_GRAY2BGR);
    std::vector<cv::Vec2f> lines;

    if (_accu == 0) return lines;

    for (int r = 0; r < _accu_h; r++)
    {
        for (int t = 0; t < _accu_w; t++)
        {
            // Searching in the accumulator a value greater
            //or equal to the set threshold
            if ((int)_accu[(r * _accu_w) + t] >= *threshold)
            {
                // Is this point a local maxima (9x9)
                int max = _accu[(r * _accu_w) + t];
                ////////////////////////////////
                for (int ly = -4; ly <= 4; ly++)
                {
                    for (int lx = -4; lx <= 4; lx++)
                    {
                        if (((ly + r) >= 0 && (ly + r) < _accu_h) &&
                                ((lx + t) >= 0 && (lx + t) < _accu_w))
                        {
                            if ((int)_accu[((r + ly) * _accu_w) + (t + lx)] > max)
                            {
                                max = _accu[((r + ly) * _accu_w) + (t + lx)];
                                ly = lx = 5;
                            }
                        }
                    }
                }
                /////////////////////////////////
                if (max > (int)_accu[(r * _accu_w) + t]) continue;

                cv::Point2f point;
                point.x = r;
                point.y = t * radian;
                lines.push_back(point);
            }
        }
    }

    return lines;
}

////////////////////////////////////////////////////////// Show Accumulator
void HoughLines::showAccum()
{
    //Visualize all
    int aw, ah, maxa;
    aw = ah = maxa = 0;
    const unsigned int* accu = _accu;
    aw = _accu_w;
    ah = _accu_h;

    for (int p = 0; p<(ah*aw); p++)
    {
        if ((int)accu[p] > maxa)
            maxa = accu[p];
    }
    double contrast = 1.0;
    double coef = 255.0 / (double)maxa * contrast;

    cv::Mat img_accu(ah, aw, CV_8UC3);
    for (int p = 0; p < (ah * aw); p++)
    {
        unsigned char c = (double) accu[p] * coef < 255.0 ?
                    (double) accu[p] * coef : 255.0;
        img_accu.data[(p * 3) + 0] = 255;
        img_accu.data[(p * 3) + 1] = 255 - c;
        img_accu.data[(p * 3) + 2] = 255 - c;
    }

    cv::imshow("Accumulator", img_accu);
    delete _accu;
}

////////////////////////////////////////////////// Drawing the lines
cv::Mat HoughLines::drawLines(std::vector<cv::Vec2f> lines)
{
    for (size_t i = 0; i < lines.size(); i++)
    {
        float r = lines[i][0], t = lines[i][1];
        cv::Point pt1, pt2;

        if (t/(CV_PI/180) >= 45 && t/(CV_PI/180) <= 135)
        {
            pt1.x = -1000;
            pt2.x = 1000;
        pt1.y = ((r - _accu_h/2) - (-1000 - _img_w / 2) * cos(t)) / sin(t) + _img_h/2;
        pt2.y = ((r - _accu_h/2) - (1000 - _img_w / 2) * cos(t)) / sin(t) + _img_h/2;
        }
        else
        {
            pt1.y = -1000;
            pt2.y = 1000;
        pt1.x = ((r - _accu_h/2) - (-1000 - _img_w / 2) * sin(t)) / cos(t) + _img_w/2;
        pt2.x = ((r - _accu_h/2) - (1000 - _img_w / 2) * sin(t)) / cos(t) + _img_w/2;
        }
        //Drawing the lines
        cv::line(_cdst, pt1, pt2, cv::Scalar(0, 0, 255), 0.1, CV_AA);
    }

    return _cdst;
}

//////////////////////////////////////////////////// Drawing the lines
cv::Mat HoughLines::drawLinesOpenCV(std::vector<cv::Vec2f> lines)
{
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta1 = lines[i][1];
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
