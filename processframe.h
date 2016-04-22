#ifndef PROCESSFRAME_H
#define PROCESSFRAME_H

#include <QObject>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include "houghlines.h"

class ProcessFrame : public QObject, public HoughLines
{
    Q_OBJECT

signals:
    void finished();
    void callShowVideo(QPixmap& x, QPixmap& y);

public:
    explicit ProcessFrame(cv::VideoCapture capWebcam1, int *index,
                          double *threshold1, double *threshold2,
                          int *apertureSize, bool *l2gradient,
                          double *rho, double *theta, int *threshold,
                          double *srn, double *stn, double *min_theta,
                          double *max_theta,
                          QObject *parent = 0);
    ~ProcessFrame();

public slots:
    void startProcessFrame();

private slots:
    void processFrameAndUpdateGUI();

private:
    cv::VideoCapture _capWebcam;       // Capture object to use with webcam

    int _index;
    double _threshold1;
    double _threshold2;
    int _apertureSize;
    bool _l2gradient;
    double _rho;
    double _theta;
    int _threshold;
    double _srn;
    double _stn;
    double _min_theta;
    double _max_theta;
};

#endif // PROCESSFRAME_H
