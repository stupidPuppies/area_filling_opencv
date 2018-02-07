#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv/cv.hpp>

#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
    if (!fileName.isNull()) {
        cv::Mat image = cv::imread(fileName.toStdString());
        cv::cvtColor(image, image, CV_BGR2RGB);
        ui->label->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888)));
    }
}

