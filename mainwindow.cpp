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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegExp exp("[0-9]+[.]\\d{1}[0-9]+");            // Validation numbers
    QValidator *validator = new QRegExpValidator(exp, this);
    ui->threshold1->setValidator(validator);
    ui->threshold2->setValidator(validator);
    ui->appertureSize->setValidator(validator);
    ui->l2gradient->setValidator(validator);

    ui->lineEdit_rho->setValidator(validator);
    ui->lineEdit_theta->setValidator(validator);
    ui->lineEdit_threshold->setValidator(validator);
    ui->lineEdit_srn->setValidator(validator);
    ui->lineEdit_stn->setValidator(validator);
    ui->lineEdit_min_theta->setValidator(validator);
    ui->lineEdit_max_theta->setValidator(validator);

    ui->lineEdit_rho_2->setValidator(validator);
    ui->lineEdit_theta_2->setValidator(validator);
    ui->lineEdit_threshold_2->setValidator(validator);
    ui->lineEdit_srn_2->setValidator(validator);
    ui->lineEdit_stn_2->setValidator(validator);
    ui->lineEdit_min_theta_2->setValidator(validator);
    ui->lineEdit_max_theta_2->setValidator(validator);

    ui->lineEdit_rho_3->setValidator(validator);
    ui->lineEdit_theta_3->setValidator(validator);
    ui->lineEdit_threshold_3->setValidator(validator);
    ui->lineEdit_srn_3->setValidator(validator);
    ui->lineEdit_stn_3->setValidator(validator);
    ui->lineEdit_min_theta_3->setValidator(validator);
    ui->lineEdit_max_theta_3->setValidator(validator);

    _index = ui->tabWidget->currentIndex();          // Get open box Index
}
MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////// Get Open Box Index
void MainWindow::on_tabWidget_tabBarClicked(int index1)
{
    _index = index1;
}

//////////////////////////////////////// Set Variables & Check empty fields
bool MainWindow::setVariables()
{

    switch(_index)
    {
    case 0:
        // Check if any fields in a form are empty
        if((ui->lineEdit->text() == "") || (ui->threshold1->text() == "") ||
           (ui->threshold2->text() == "") || (ui->appertureSize->text() == "") ||
           (ui->l2gradient->text() == "") || (ui->lineEdit_rho_2->text() == "") ||
           (ui->lineEdit_theta_2->text() == "") || (ui->lineEdit_threshold_2->text() == "") ||
           (ui->lineEdit_srn_2->text() == "") || (ui->lineEdit_stn_2->text() == "") ||
           (ui->lineEdit_min_theta_2->text() == "") || (ui->lineEdit_max_theta_2->text() == ""))
        {
            // Show error message
            QMessageBox::information(this, "ERROR: Empty fields!!!",
                                     "There are empty fields!"
                                     "\nPlease complete all fields.");
            return false;
        }
        else {
            // Set Variables
            _file = ui->lineEdit->text();
            _threshold1 = ui->threshold1->text().toDouble();
            _threshold2 = ui->threshold2->text().toDouble();
            _apertureSize = ui->appertureSize->text().toInt();
            _l2gradient = ui->l2gradient->text().toInt();
            _rho = ui->lineEdit_rho_2->text().toDouble();
            _theta = ui->lineEdit_theta_2->text().toDouble();
            _threshold = ui->lineEdit_threshold_2->text().toInt();
            _srn = ui->lineEdit_srn_2->text().toDouble();
            _stn = ui->lineEdit_stn_2->text().toDouble();
            _min_theta = ui->lineEdit_min_theta_2->text().toDouble();
            _max_theta = ui->lineEdit_max_theta_2->text().toDouble();
            return true;
        }
        break;
    case 1:
        // Check if any fields in a form are empty
        if((ui->lineEdit->text() == "") || (ui->threshold1->text() == "") ||
           (ui->threshold2->text() == "") || (ui->appertureSize->text() == "") ||
           (ui->l2gradient->text() == "") || (ui->lineEdit_rho->text() == "") ||
           (ui->lineEdit_theta->text() == "") || (ui->lineEdit_threshold->text() == "") ||
           (ui->lineEdit_srn->text() == "") || (ui->lineEdit_stn->text() == "") ||
           (ui->lineEdit_min_theta->text() == "") || (ui->lineEdit_max_theta->text() == ""))
        {
            // Show error message
            QMessageBox::information(this, "ERROR: Empty fields!!!",
                                     "There are empty fields!"
                                     "\nPlease complete all fields.");
            return false;
        }
        else {
            // Set Variables
            _file = ui->lineEdit->text();
            _threshold1 = ui->threshold1->text().toDouble();
            _threshold2 = ui->threshold2->text().toDouble();
            _apertureSize = ui->appertureSize->text().toInt();
            _l2gradient = ui->l2gradient->text().toInt();
            _rho = ui->lineEdit_rho->text().toDouble();
            _theta = ui->lineEdit_theta->text().toDouble();
            _threshold = ui->lineEdit_threshold->text().toInt();
            _srn = ui->lineEdit_srn->text().toDouble();
            _stn = ui->lineEdit_stn->text().toDouble();
            _min_theta = ui->lineEdit_min_theta->text().toDouble();
            _max_theta = ui->lineEdit_max_theta->text().toDouble();
            return true;
        }
        break;
    case 2:
        // Check if any fields in a form are empty
        if((ui->lineEdit->text() == "") || (ui->threshold1->text() == "") ||
           (ui->threshold2->text() == "") || (ui->appertureSize->text() == "") ||
           (ui->l2gradient->text() == "") || (ui->lineEdit_rho_3->text() == "") ||
           (ui->lineEdit_theta_3->text() == "") || (ui->lineEdit_threshold_3->text() == "") ||
           (ui->lineEdit_srn_3->text() == "") || (ui->lineEdit_stn_3->text() == "") ||
           (ui->lineEdit_min_theta_3->text() == "") || (ui->lineEdit_max_theta_3->text() == ""))
        {
            // Show error message
            QMessageBox::information(this, "ERROR: Empty fields!!!",
                                     "There are empty fields!"
                                     "\nPlease complete all fields.");
            return false;
        }
        else {
            // Set Variables
            _file = ui->lineEdit->text();
            _threshold1 = ui->threshold1->text().toDouble();
            _threshold2 = ui->threshold2->text().toDouble();
            _apertureSize = ui->appertureSize->text().toInt();
            _l2gradient = ui->l2gradient->text().toInt();
            _rho = ui->lineEdit_rho_3->text().toDouble();
            _theta = ui->lineEdit_theta_3->text().toDouble();
            _threshold = ui->lineEdit_threshold_3->text().toInt();
            _srn = ui->lineEdit_srn_3->text().toDouble();
            _stn = ui->lineEdit_stn_3->text().toDouble();
            _min_theta = ui->lineEdit_min_theta_3->text().toDouble();
            _max_theta = ui->lineEdit_max_theta_3->text().toDouble();
            return true;
        }
        break;
    default:
        return false;
    }
}

/////////////////////////////////////Creation obj Canny
void MainWindow::on_pushButton_clicked()
{
    if(setVariables()) {
        _canny = new Canny(&_index, &_file, &_threshold1,
                           &_threshold2, &_apertureSize,
                           &_l2gradient, &_rho, &_theta,
                           &_threshold, &_srn, &_stn,
                           &_min_theta, &_max_theta);
        _canny->setAttribute(Qt::WA_DeleteOnClose);
        _canny->show();
    }
}

//////////////////////////////////////// Creation obj Capture
void MainWindow::on_pushButton_4_clicked()
{
    if(setVariables()) {
        _capture = new Capture();
        _capture->setAttribute(Qt::WA_DeleteOnClose);
        _capture->show();
        _capture->startThreadsAndTransformHough(&_index, &_threshold1,
                                                &_threshold2, &_apertureSize,
                                                &_l2gradient, &_rho, &_theta,
                                                &_threshold, &_srn, &_stn,
                                                &_min_theta, &_max_theta);
        // Set Disable Button then Capture will be opened
        ui->pushButton_4->setEnabled(false);
        // Set Enabled Button then Capture will be closed
        connect(_capture, SIGNAL(quit()), this, SLOT(pushButton_4()));
    }
}

////////////////////////////// Set Enabled Button then Capture will be closed
void MainWindow::pushButton_4()
{
    ui->pushButton_4->setEnabled(true);
}

//////////////////////////////////////////////// Open_File, Loading FileName
void MainWindow::on_pushButton_2_clicked()
{
    QStringList file;
    QStringList filters;
    filters << "Image files (*.png *.xpm *.jpg)";

    QFileDialog dialog;
    dialog.setNameFilters(filters);

    if(dialog.exec()) {
        file = dialog.selectedFiles();             // Load file_name
    }
    else {return;}

    ui->lineEdit->setText(file[0]);
    ui->textBrowser->append(file[0]);
}

//////////////////////////////////////////// Converting Radians to Degrees
void MainWindow::on_lineEdit_degree_textChanged(const QString &arg1)
{
    double x = arg1.toDouble() * CV_PI / 180;
    ui->lineEdit_theta->setText(QString::number(x));
}

void MainWindow::on_lineEdit_degree_2_textChanged(const QString &arg1)
{
    double x = arg1.toDouble() * CV_PI / 180;
    ui->lineEdit_theta_2->setText(QString::number(x));
}


/////////////////////////////////////////////// Converting Bool to Int
void MainWindow::on_l2gradient_2_textChanged(const QString &arg1)
{
    if (arg1 == "true") ui->l2gradient->setText("1");
    else ui->l2gradient->setText("0");
}

///////////////////////////////////////////////// Exit button
void MainWindow::on_pushButton_3_clicked()
{
    this->close();
}

//////////////////////////////////////////////// Overload "close()"
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

