#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv/cv.hpp>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <vector>

#include "cannytesterwindow.h"
#include "imgoperate.h"
#include "dragablelabel.h"

MainWindow *this_window;

using namespace cv;


double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2) / sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new DragableLabel(this);
    label->imgop = &imgop;
    ui->verticalLayout->addWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
   if (!fileName.isNull()) {
       imgop.LoadMainImage(fileName);
       label->setPixmap(imgop.GetCanvas());
       label->points = imgop.CurrentSquare();
       label->update();
   }
}

void MainWindow::on_nextButton_clicked()
{
    if (!imgop.IsEmpty()) {
        label->points = imgop.NextSquare();
        label->setPixmap(imgop.GetCanvas());
        label->update();
    }
}

void MainWindow::on_pushButton_clicked()
{
    CannyTesterWindow *ctw = new CannyTesterWindow;
    ctw->show();
    this->hide();
}

void MainWindow::on_replaceButton_clicked()
{
    if (!imgop.IsEmpty()) {
        QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
        if (!fileName.isNull()) {
            imgop.LoadReplaceImage(fileName);
            label->setPixmap(imgop.GetCanvas());
            label->update();
        }
    }
}

void MainWindow::on_prevButton_clicked()
{
    if (!imgop.IsEmpty()) {
        label->points = imgop.PreviousSquare();
        label->setPixmap(imgop.GetCanvas());
        label->update();
    }
}

void MainWindow::on_saveButton_clicked()
{
    if (!imgop.IsEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this,"Save",".","JPEG Files(*.jpg);;PNG Files(*.png)");
        if (!fileName.isNull()) {
            imgop.SaveImage(fileName);
        }
    }
}
