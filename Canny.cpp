#include "Canny.h"
#include "ui_Canny.h"
#include "mattoqimage.h"
#include "houghlines.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include "QFileDialog"
#include "QStandardPaths"
#include <QElapsedTimer>

Canny::Canny(QString *file, double *threshold1, double *threshold2,
             int *apertureSize, bool *L2gradient,
             double *rho, double *theta, int *threshold, double *srn,
             double *stn, double *min_theta, double *max_theta,
             QWidget *parent) : QWidget(parent), ui(new Ui::Canny)
{
    ui->setupUi(this);

    QElapsedTimer timer;                                            //Timer
    timer.start();                                                  //Start timer

    std::string Sfilename = file->toStdString();

    Append(file, threshold1, threshold2, apertureSize, L2gradient,
           rho, theta, threshold, srn, stn, min_theta, max_theta);  //Display variables

    cv::Mat scr, dst;
    scr = cv::imread(Sfilename, 0);

    cv::Canny(scr, dst, *threshold1, *threshold2,
              *apertureSize, *L2gradient);                      //Canny Edge Detector

    QImage x = Mat2Qimage(dst);               //Convert from OpenCV cv::Mat to Qt QPixmap
    ui->label_2->setPixmap(QPixmap::fromImage(x));

    //////////////////////////////////////////

    QImage y = Mat2Qimage(Hough1(&dst, rho, theta,              //Hough Line Transform
                                 threshold, srn, stn,
                                 min_theta, max_theta));
    ui->label_3->setPixmap(QPixmap::fromImage(y));

    //////////////////////////////////////////
    QString ms;
    ms.append("Milliseconds: ");
    ms.append(QString::number(timer.elapsed()));
    ui->textBrowser->append(ms);                         //Show received time from Timer
}
Canny::~Canny()
{
    delete ui;
}

////////////////////////////////////////////////////Show information (all variables)
void Canny::Append(QString *file, double *threshold1, double *threshold2,
                   int *apertureSize, bool *L2gradient,
                   double *rho, double *theta, int *threshold, double *srn,
                   double *stn, double *min_theta, double *max_theta)
{
    ui->textBrowser->append(*file);
    QString x, y;
    x.append(QString::number(*threshold1));
    x.append(", ");
    x.append(QString::number(*threshold2));
    x.append(", ");
    x.append(QString::number(*apertureSize));
    x.append(", ");
    if (*L2gradient == 1) x.append("true");
    else x.append("false");
    ui->textBrowser->append(x);

    y.append(QString::number(*rho));
    y.append(", ");
    y.append(QString::number(*theta));
    y.append(", ");
    y.append(QString::number(*threshold));
    y.append(", ");
    y.append(QString::number(*srn));
    y.append(", ");
    y.append(QString::number(*stn));
    y.append(", ");
    y.append(QString::number(*min_theta));
    y.append(", ");
    y.append(QString::number(*max_theta));
    ui->textBrowser->append(y);
}
