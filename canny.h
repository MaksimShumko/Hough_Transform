#ifndef CANNY_H
#define CANNY_H

#include <QWidget>
#include "transform.h"
#include "mytransform.h"
#include "opencvtransform.h"

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
    explicit Canny(int *index, QString *file, double *threshold1,
                   double *threshold2, int *apertureSize, bool *l2gradient,
                   double *rho, double *theta, int *threshold, double *srn,
                   double *stn, double *min_theta, double *max_theta,
                   QWidget *parent = 0);
    ~Canny();

private:
    Ui::Canny *ui;

    void Canny::displayVariables(QString *file, double *threshold1,
                                 double *threshold2, int *apertureSize,
                                 bool *l2gradient, double *rho, double *theta,
                                 int *threshold, double *srn, double *stn,
                                 double *min_theta, double *max_theta);
};

#endif // CANNY_H
