#ifndef CANNY_H
#define CANNY_H

#include <QWidget>
#include "houghlines.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
class Canny;
}

class Canny : public QWidget
{
    Q_OBJECT

public:
    explicit Canny(QString *file, double *threshold1, double *threshold2,
                   int *apertureSize, bool *L2gradient,
                   double *rho, double *theta, int *threshold, double *srn,
                   double *stn, double *min_theta, double *max_theta,
                   QWidget *parent = 0);
    ~Canny();

    void Canny::Append(QString *file, double *threshold1, double *threshold2,
                       int *apertureSize, bool *L2gradient,
                       double *rho, double *theta, int *threshold, double *srn,
                       double *stn, double *min_theta, double *max_theta);

private:
    Ui::Canny *ui;
};

#endif // CANNY_H
