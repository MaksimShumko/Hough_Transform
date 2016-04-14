#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/imgcodecs/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include <iostream>
#include "QFileDialog"
#include "QStandardPaths"
#include "QWidget"
#include "qmessagebox"
#include "qcloseevent"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp exp("[0-9]+[.]\\d{1}[0-9]+");                                                      //Validation numbers
    QValidator *validator = new QRegExpValidator(exp, this);
    ui->Threshold1->setValidator(validator);
    ui->Threshold2->setValidator(validator);
    ui->appertureSize->setValidator(validator);
    ui->L2gradient->setValidator(validator);
    ui->lineEdit_rho->setValidator(validator);
    ui->lineEdit_theta->setValidator(validator);
    ui->lineEdit_threshold->setValidator(validator);
    ui->lineEdit_srn->setValidator(validator);
    ui->lineEdit_stn->setValidator(validator);
    ui->lineEdit_min_theta->setValidator(validator);
    ui->lineEdit_max_theta->setValidator(validator);
}
MainWindow::~MainWindow()
{
    delete ui;
}

//////////////////////////////////////////////////Set Variables & Check empty fields
bool MainWindow::set_Variables()
{
    if((ui->lineEdit->text() == "") || (ui->Threshold1->text() == "") ||
            (ui->Threshold2->text() == "") || (ui->appertureSize->text() == "") ||
            (ui->L2gradient->text() == "") || (ui->lineEdit_rho->text() == "") ||
            (ui->lineEdit_theta->text() == "") || (ui->lineEdit_threshold->text() == "") ||
            (ui->lineEdit_srn->text() == "") || (ui->lineEdit_stn->text() == "") ||
            (ui->lineEdit_min_theta->text() == "") || (ui->lineEdit_max_theta->text() == ""))   //Check if any fields in a form are empty
    {
        QMessageBox::information(this, "ERROR: Empty fields!!!",
                                 "There are empty fields!\nPlease complete all fields.");        // show error message
        return false;
    }
    else {
        file = ui->lineEdit->text();
        threshold1 = ui->Threshold1->text().toDouble();
        threshold2 = ui->Threshold2->text().toDouble();
        apertureSize = ui->appertureSize->text().toInt();
        L2gradient = ui->L2gradient->text().toInt();
        rho = ui->lineEdit_rho->text().toDouble();
        theta = ui->lineEdit_theta->text().toDouble();
        threshold = ui->lineEdit_threshold->text().toInt();
        srn = ui->lineEdit_srn->text().toDouble();
        stn = ui->lineEdit_stn->text().toDouble();
        min_theta = ui->lineEdit_min_theta->text().toDouble();
        max_theta = ui->lineEdit_max_theta->text().toDouble();
        return true;
    }
}

//////////////////////////////////////////////////Creation obj Canny
void MainWindow::on_pushButton_clicked()
{
    if(set_Variables()) {
        Canny1 = new Canny(&file, &threshold1, &threshold2, &apertureSize, &L2gradient,
                           &rho, &theta, &threshold, &srn, &stn, &min_theta, &max_theta);
        Canny1->setAttribute(Qt::WA_DeleteOnClose);
        Canny1->show();
    }
}

//////////////////////////////////////////////////Creation obj Capture
void MainWindow::on_pushButton_4_clicked()
{
    if(set_Variables()) {
        Capture1 = new capture(&threshold1, &threshold2, &apertureSize, &L2gradient,
                               &rho, &theta, &threshold, &srn, &stn, &min_theta, &max_theta);
        Capture1->setAttribute(Qt::WA_DeleteOnClose);
        Capture1->show();
    }
}

//////////////////////////////////////////////////Open_File, Loading FileName
void MainWindow::on_pushButton_2_clicked()
{
    QStringList file;
    QStringList filters;
    filters << "Image files (*.png *.xpm *.jpg)";

    QFileDialog dialog;
    dialog.setNameFilters(filters);

    if(dialog.exec()) {
        file = dialog.selectedFiles();                                                    //Load file_name
    }
    else {return;}

    ui->lineEdit->setText(file[0]);
    ui->textBrowser->append(file[0]);
}

//////////////////////////////////////////////////Converting Radians to Degrees
void MainWindow::on_lineEdit_degree_textChanged(const QString &arg1)
{
    double x = arg1.toDouble() * CV_PI / 180;
    ui->lineEdit_theta->setText(QString::number(x));
}

//////////////////////////////////////////////////Converting Bool to Int
void MainWindow::on_L2gradient_2_textChanged(const QString &arg1)
{
    if (arg1 == "true") ui->L2gradient->setText("1");
    else ui->L2gradient->setText("0");
}

/////////////////////////////////////////////////////Exit button
void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

///////////////////////////////////////////////////Overload "close()"
void MainWindow::closeEvent(QCloseEvent *event)
{
    int quit = QMessageBox::information(this,
                    "Really quit?", "Are you sure?", tr("Yes"), tr("No"));
    if (quit == 0) {
        qApp->closeAllWindows();
        event->accept();
    }
    else event->ignore();
}
