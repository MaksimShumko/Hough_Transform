#include "capture.h"
#include "ui_capture.h"
#include "mattoqimage.h"

#include <opencv\cv.h>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include<QtCore>
#include<QMessageBox>
#include "houghlines.h"
#include "QElapsedTimer"
#include <QThread>
#include "QtConcurrent/QtConcurrentRun"
#include <QCloseEvent>


capture::capture(double *threshold1, double *threshold2,
                 int *apertureSize, bool *L2gradient,
                 double *rho, double *theta, int *threshold,
                 double *srn, double *stn, double *min_theta, double *max_theta,
                 QWidget *parent) :  QWidget(parent), ui(new Ui::capture)
{
    ui->setupUi(this);

    capWebcam.open(0);                                          // associate the capture object to the default webcam

    if(capWebcam.isOpened() == false) {                                                     // if unsuccessful
        QMessageBox::information(this, "",
                   "error: capWebcam not accessed successfully \n\n exiting program\n");        // show error message
        exitProgram();                                                                        // and exit program
        return;
    }

    ////////////////////////////////////////////////////////////////Threads
    qRegisterMetaType<QPixmap>("QPixmap&");

    for (int i = 0; i < 4; i++)                                     //Creating 4 threads & 4 obj ProcessFrame in these threads
    {
        thread[i] = new QThread(this);
        process[i] = new ProcessFrame(capWebcam, threshold1, threshold2, apertureSize, L2gradient,
                                      rho, theta, threshold, srn, stn,
                                      min_theta, max_theta);
        process[i]->moveToThread(thread[i]);
        connect(process[i], SIGNAL(error(QString)), this, SLOT(errorString(QString)));
        connect(thread[i], SIGNAL(started()), process[i], SLOT(process()));
        connect(process[i], SIGNAL(finished()), thread[i], SLOT(quit()));
        connect(process[i], SIGNAL(finished()), process[i], SLOT(deleteLater()));
        connect(thread[i], SIGNAL(finished()), thread[i], SLOT(deleteLater()));

        connect(process[i], SIGNAL(call_showV(QPixmap&, QPixmap&)), this, SLOT(showV(QPixmap&, QPixmap&)));
        thread[i]->start();
    }

    QTimer* qtimer;                                             // timer for Fps()
    qtimer = new QTimer(this);                                   // instantiate timer
    connect(qtimer, SIGNAL(timeout()), this, SLOT(Fps()));     // associate timer to Fps()
    qtimer->start(1000);                                    // start timer, set to cycle every 1000 msec (1x per sec)
}
capture::~capture()
{
    delete ui;
}

///////////////////////////////////////////////////Exit
void capture::exitProgram()
{
    this->close();                          //Exit program
}

///////////////////////////////////////////////////Overload "close()"
void capture::closeEvent(QCloseEvent *event)
{
    for (int i = 0; i < 4; i++)             //Delete Threads & Objects
    {
        thread[i]->deleteLater();
        process[i]->deleteLater();
    }
    event->accept();
}

////////////////////////////////////////////////////Show video
void capture::showV(QPixmap& x, QPixmap& y)
{
    mutex1.lock();                  //Mutex (Semaphore)
    ui->label->setPixmap(x);        //Show Original_Video
    mutex1.unlock();

    mutex2.lock();
    ui->label_2->setPixmap(y);      //Show Hough_Video
    mutex2.unlock();

    mutex3.lock();                  //Frame rate
    fps++;
    ui->lcdNumber_2->display(fps);
    mutex3.unlock();
}

////////////////////////////////////////////////////Frame rate
void capture::Fps()
{
    int x = fps - fps_x;
    fps_x = fps;
    x /= 1;
    ui->lcdNumber->display(x);
}
