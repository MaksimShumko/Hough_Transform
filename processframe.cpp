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


ProcessFrame::ProcessFrame(cv::VideoCapture capWebcam1, double *_threshold1, double *_threshold2,
                           int *_apertureSize, bool *_L2gradient,
                           double *_rho, double *_theta, int *_threshold,
                           double *_srn, double *_stn, double *_min_theta, double *_max_theta,
                           QObject *parent) : QObject(parent)
{
    capWebcam = capWebcam1;                                                         //Set Variables

    threshold1 = *_threshold1;
    threshold2 = *_threshold2;
    apertureSize = *_apertureSize;
    L2gradient = *_L2gradient;
    rho = *_rho;
    theta = *_theta;
    threshold = *_threshold;
    srn = *_srn;
    stn = *_stn;
    min_theta = *_min_theta;
    max_theta = *_max_theta;
}
ProcessFrame::~ProcessFrame() {
}

void ProcessFrame::process()
{
    QTimer* qtimer;                                                                // timer for processFrameAndUpdateGUI()
    qtimer = new QTimer(this);                                                      // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(processFrameAndUpdateGUI()));   // associate timer to processFrameAndUpdateGUI()
    qtimer->start();                                                                    // start timer
}

void ProcessFrame::processFrameAndUpdateGUI()
{
    cv::Mat imgOriginal, dst;                                                           // input image

    capWebcam.read(imgOriginal);                                                        // get next frame from the webcam

    if (imgOriginal.empty()) {                                                          // if we did not get a frame
        //QMessageBox::information(capture, "", "unable to read from "
        //                                   "webcam \n\n exiting program\n");        // show error via message box
        emit finished();                                                                 // and exit program
        return;
    }

    cv::Canny(imgOriginal, dst, threshold1, threshold2, apertureSize, L2gradient);  //Canny Edge Detector

    QPixmap &qimgOriginal = QPixmap::fromImage(Mat2Qimage(imgOriginal));             //Convert from OpenCV Mat to Qt QImage
    QPixmap &cdst = QPixmap::fromImage(Mat2Qimage(Hough1(&dst, &rho, &theta,        //Hough Line Transform
                                 &threshold, &srn, &stn,
                                 &min_theta, &max_theta)));                          //Convert from OpenCV Mat to Qt QImage

    emit call_showV(qimgOriginal, cdst);
}
