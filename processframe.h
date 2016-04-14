#ifndef PROCESSFRAME_H
#define PROCESSFRAME_H

#include <QObject>

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

class ProcessFrame : public QObject
{
    Q_OBJECT
public:
    explicit ProcessFrame(cv::VideoCapture capWebcam1, double *_threshold1, double *_threshold2, int *_apertureSize, bool *_L2gradient,
                          double *_rho, double *_theta, int *_threshold, double *_srn, double *_stn, double *_min_theta, double *_max_theta,
                          QObject *parent = 0);
    ~ProcessFrame();

signals:
    void finished();
    void error(QString err);
    void call_showV(QPixmap& x, QPixmap& y);

public slots:
    void processFrameAndUpdateGUI();
    void process();

private:
    cv::VideoCapture capWebcam;         // Capture object to use with webcam

    double threshold1;
    double threshold2;
    int apertureSize;
    bool L2gradient;
    double rho;
    double theta;
    int threshold;
    double srn;
    double stn;
    double min_theta;
    double max_theta;
};

#endif // PROCESSFRAME_H
