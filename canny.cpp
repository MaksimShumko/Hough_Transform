#include "canny.h"
#include "ui_canny.h"
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

Canny::Canny(int *index, QString *file, double *threshold1, double *threshold2,
             int *apertureSize, bool *l2gradient,
             double *rho, double *theta, int *threshold, double *srn,
             double *stn, double *min_theta, double *max_theta,
             QWidget *parent) : QWidget(parent), ui(new Ui::Canny)
{
    ui->setupUi(this);

    QElapsedTimer timer;      // Timer
    timer.start();            // Start timer

    std::string stringFilename = file->toStdString();

    // Display variables
    displayVariables(file, threshold1, threshold2, apertureSize, l2gradient,
           rho, theta, threshold, srn, stn, min_theta, max_theta);

    cv::Mat scr, dst;
    scr = cv::imread(stringFilename, 0);

    // Canny Edge Detector
    cv::Canny(scr, dst, *threshold1, *threshold2,
              *apertureSize, *l2gradient);
    // Convert from OpenCV cv::Mat to Qt QPixmap
    QImage x = convertMat2Qimage(dst);
    ui->label_2->setPixmap(QPixmap::fromImage(x));

    //////////////////////////////////////////
    std::vector<cv::Vec2f> houghVec;
    cv::Mat draw;
    switch(*index)
    {
    case 0:
        // My Hough Line Transform
        houghVec = houghTransform(&dst, rho, theta,
                                      threshold, srn, stn,
                                      min_theta, max_theta);
        draw = drawLines(houghVec);
        // Show Accumulator
        showAccum();
        break;
    case 1:
        // OpenCV Hough Line Transform
        houghVec = houghTransformOpenCV(&dst, rho, theta,
                                      threshold, srn, stn,
                                      min_theta, max_theta);
        draw = drawLinesOpenCV(houghVec);
        break;
    case 3:
        this->close();
        break;
    default:
        this->close();
    }

    QImage y = convertMat2Qimage(draw);
    ui->label_3->setPixmap(QPixmap::fromImage(y));

    //////////////////////////////////////////
    QString ms;
    ms.append("Milliseconds: ");
    ms.append(QString::number(timer.elapsed()));
    // Show received time from Timer
    ui->textBrowser->append(ms);


}
Canny::~Canny()
{
    delete ui;
}

//////////////////////////////////////////////Show information (all variables)
void Canny::displayVariables(QString *file, double *threshold1,
                             double *threshold2, int *apertureSize,
                             bool *l2gradient, double *rho, double *theta,
                             int *threshold, double *srn, double *stn,
                             double *min_theta, double *max_theta)
{
    ui->textBrowser->append(*file);
    QString x, y;
    x.append(QString::number(*threshold1));
    x.append(", ");
    x.append(QString::number(*threshold2));
    x.append(", ");
    x.append(QString::number(*apertureSize));
    x.append(", ");
    if (*l2gradient == 1) x.append("true");
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
