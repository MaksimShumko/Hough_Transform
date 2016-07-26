#ifndef CAPTURE_H
#define CAPTURE_H

#include "processframe.h"

#include <QWidget>
#include <QThread>
#include <QPixmap>
#include <QMutex>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>


namespace Ui {
class Capture;
}

class Capture : public QWidget
{
    Q_OBJECT

signals:
    void quit();

public:
    Capture(QWidget *parent = 0);
    ~Capture();

    void startThreadsAndTransformHough(int *index, double *threshold1,
                                       double *threshold2, int *apertureSize,
                                       bool *l2gradient, double *rho,
                                       double *theta, int *threshold,
                                       double *srn, double *stn,
                                       double *min_theta, double *max_theta);

public slots:
    void showVideo(QPixmap& x, QPixmap &y);

private slots:
    void indicateFrameRate();

private:
    Ui::Capture *ui;

    cv::VideoCapture _capWebcam;      // Capture object to use with webcam
    virtual void closeEvent(QCloseEvent *event);

    QThread *_thread[4];
    ProcessFrame* _process[4];

    QMutex _mutex1, _mutex2, _mutex3;

    int _fps = 0, _fpsBuf = 0;
};

#endif // CAPTURE_H
