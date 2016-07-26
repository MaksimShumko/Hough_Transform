#include "capture.h"
#include "ui_capture.h"
#include "mattoqimage.h"

#include "processframe.h"

#include <opencv\cv.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include <QtCore>
#include <QMessageBox>
#include "QElapsedTimer"
#include <QThread>
#include "QtConcurrent/QtConcurrentRun"
#include <QCloseEvent>


Capture::Capture(QWidget *parent) :  QWidget(parent), ui(new Ui::Capture)
{
    ui->setupUi(this);

    // Associate the capture object to the default webcam
    _capWebcam.open(0);

    // If unsuccessful
    if(_capWebcam.isOpened() == false) {
        // Show error message
        QMessageBox::information(this, "",
                   "error: capWebcam not accessed successfully "
                   "\n\n exiting program\n");
        // And exit program
        this->close();
        return;
    }

    // Timer for indicateFrameRate()
    QTimer* qtimer;
    // Instantiate timer
    qtimer = new QTimer(this);
    // Associate timer to indicateFrameRate()
    connect(qtimer, SIGNAL(timeout()), this, SLOT(indicateFrameRate()));
    // Start timer, set to cycle every 1000 msec (1x per sec)
    qtimer->start(1000);
}
Capture::~Capture()
{
    delete ui;
}

//////////////////////////////////////// Threads and Proces of Hough Transform
void Capture::startThreadsAndTransformHough(int *index, double *threshold1,
                                            double *threshold2, int *apertureSize,
                                            bool *l2gradient, double *rho,
                                            double *theta, int *threshold,
                                            double *srn, double *stn,
                                            double *min_theta, double *max_theta)
{
    qRegisterMetaType<QPixmap>("QPixmap&");

    // Creating 4 threads & 4 obj ProcessFrame in these threads
    for (int i = 0; i < 4; i++)
    {
        _thread[i] = new QThread();
        _process[i] = new ProcessFrame(_capWebcam, index, threshold1, threshold2,
                                       apertureSize, l2gradient, rho, theta,
                                       threshold, srn, stn, min_theta, max_theta);
        _process[i]->moveToThread(_thread[i]);
        connect(_thread[i], SIGNAL(started()), _process[i], SLOT(startProcessFrame()));
        connect(_process[i], SIGNAL(finished()), _thread[i], SLOT(quit()));
        connect(_process[i], SIGNAL(finished()), _process[i], SLOT(deleteLater()));
        connect(_thread[i], SIGNAL(finished()), _thread[i], SLOT(deleteLater()));

        connect(_process[i], SIGNAL(callShowVideo(QPixmap&, QPixmap&)),
                this, SLOT(showVideo(QPixmap&, QPixmap&)));
        _thread[i]->start();
    }
}

/////////////////////////////////////////////////// Override "close()"
void Capture::closeEvent(QCloseEvent *event)
{
    emit quit();
    for (int i = 0; i < 4; i++)             // Delete Threads & Objects
    {
        _process[i]->deleteLater();
        _process[i]->stop();
    }
    event->accept();
}

//////////////////////////////////////////////////// Show video
void Capture::showVideo(QPixmap& x, QPixmap& y)
{
    _mutex1.lock();                  // Mutex (Semaphore)
    ui->label->setPixmap(x);        // Show Original_Video
    _mutex1.unlock();

    _mutex2.lock();
    ui->label_2->setPixmap(y);      // Show Hough_Video
    _mutex2.unlock();

    _mutex3.lock();                  // Frame rate
    _fps++;
    ui->lcdNumber_2->display(_fps);
    _mutex3.unlock();
}

//////////////////////////////////////////////////// Frame rate
void Capture::indicateFrameRate()
{
    int x = _fps - _fpsBuf;
    _fpsBuf = _fps;
    x /= 1;
    ui->lcdNumber->display(x);
}
