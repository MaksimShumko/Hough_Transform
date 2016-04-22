#include "processframe.h"

#include "mattoqimage.h"
#include "capture.h"

#include <opencv\cv.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include <QtCore>
#include <QMessageBox>
#include "houghlines.h"
#include "QElapsedTimer"
#include <QThread>
#include "QtConcurrent/QtConcurrentRun"
#include <QCloseEvent>


ProcessFrame::ProcessFrame(cv::VideoCapture capWebcam1, int *index,
                           double *threshold1, double *threshold2,
                           int *apertureSize, bool *l2gradient,
                           double *rho, double *theta, int *threshold,
                           double *srn, double *stn, double *min_theta,
                           double *max_theta,
                           QObject *parent) : QObject(parent)
{
    // Set Variables
    _capWebcam = capWebcam1;

    _index = *index;
    _threshold1 = *threshold1;
    _threshold2 = *threshold2;
    _apertureSize = *apertureSize;
    _l2gradient = *l2gradient;
    _rho = *rho;
    _theta = *theta;
    _threshold = *threshold;
    _srn = *srn;
    _stn = *stn;
    _min_theta = *min_theta;
    _max_theta = *max_theta;
}
ProcessFrame::~ProcessFrame()
{

}

///////////////////////////////// Timer for processFrameAndUpdateGUI()
void ProcessFrame::startProcessFrame()
{
    QTimer* qtimer;
    // Instantiate timer
    qtimer = new QTimer(this);
    // Associate timer to processFrameAndUpdateGUI()
    connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));
    // Start timer
    qtimer->start();
}

/////////////////////////////////////////////////// Transform and send to GUI
void ProcessFrame::processFrameAndUpdateGUI()
{
    cv::Mat imgOriginal, dst;

    _capWebcam.read(imgOriginal);       // Get next frame from the webcam

    // Canny Edge Detector
    cv::Canny(imgOriginal, dst, _threshold1, _threshold2,
              _apertureSize, _l2gradient);

    //Convert from OpenCV Mat to Qt QImage
    QPixmap &qimgOriginal = QPixmap::fromImage(convertMat2Qimage(imgOriginal));

    std::vector<cv::Vec2f> hough;
    cv::Mat draw;
    switch(_index)
    {
    case 0:
        // My Hough Line Transform
        hough = houghTransform(&dst, &_rho, &_theta,
                               &_threshold, &_srn, &_stn,
                               &_min_theta, &_max_theta);
        draw = drawLines(hough);
        showAccum();                    // Show Accumulator
        break;
    case 1:
        // OpenCV Hough Line Transform
        hough = houghTransformOpenCV(&dst, &_rho, &_theta,
                                      &_threshold, &_srn, &_stn,
                                      &_min_theta, &_max_theta);
        draw = drawLinesOpenCV(hough);
        break;
    case 3:
        emit finished();
        break;
    default:
        emit finished();
    }

    // Convert from OpenCV Mat to Qt QImage
    QPixmap &cdst = QPixmap::fromImage(convertMat2Qimage(draw));

    emit callShowVideo(qimgOriginal, cdst);        // Send images to Parent
}
