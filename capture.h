#ifndef CAPTURE_H
#define CAPTURE_H

#include <QWidget>
#include <QThread>
#include <QPixmap>
#include <QMutex>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "processframe.h"

namespace Ui {
class capture;
}

class capture : public QWidget
{
    Q_OBJECT

public:
    explicit capture(double *threshold1, double *threshold2,
                     int *apertureSize, bool *L2gradient,
                     double *rho, double *theta, int *threshold,
                     double *srn, double *stn, double *min_theta, double *max_theta,
                     QWidget *parent = 0);
    ~capture();

public slots:
    void Fps();
    void showV(QPixmap& x, QPixmap &y);

private:
    Ui::capture *ui;

    void exitProgram();
    cv::VideoCapture capWebcam;  // Capture object to use with webcam
    virtual void closeEvent(QCloseEvent *event);

    QThread *thread[4];
    ProcessFrame *process[4];

    QMutex mutex1, mutex2, mutex3;

    int fps = 0, fps_x = 0;
};

#endif // CAPTURE_H
