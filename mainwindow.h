#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "Canny.h"
#include "capture.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_degree_textChanged(const QString &arg1);

    void on_L2gradient_2_textChanged(const QString &arg1);

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

    virtual void closeEvent(QCloseEvent *event);
    Canny *Canny1;
    capture *Capture1;

    QString file;
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

    bool set_Variables();
};

#endif // MAINWINDOW_H
