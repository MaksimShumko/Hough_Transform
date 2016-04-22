#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include "canny.h"
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
    void on_l2gradient_2_textChanged(const QString &arg1);
    void on_pushButton_4_clicked();
    void pushButton_4();
    void on_tabWidget_tabBarClicked(int index1);
    void on_lineEdit_degree_2_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    virtual void closeEvent(QCloseEvent *event);
    Canny *_canny;
    Capture *_capture;

    int _index;
    QString _file;
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

    bool setVariables();
};

#endif // MAINWINDOW_H
