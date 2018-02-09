#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv/cv.hpp>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>

#include "imgoperate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    imgop = ImgOperate(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
   imgop.loagImg(fileName);
   imgop.process();

   //    if (!fileName.isNull()) {
//        cv::Mat image = cv::imread(fileName.toStdString());
//        cv::cvtColor(image, image, CV_BGR2RGB);
//        ui->label->setPixmap(QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888)));
//    }
}

void MainWindow::on_nextButton_clicked()
{
    static int i = -1;
    i++;
    Mat image;
    cv::cvtColor(imgop.img, image, CV_BGR2RGB);
    QPixmap pixmap = QPixmap::fromImage(QImage(image.data, image.cols, image.rows, image.step, QImage::Format_RGB888));
    QPainter painter(&pixmap);
    struct CntInfo cnt = imgop.cnts[i];
    for(int j=0;j<4;j++){
        painter.drawEllipse(QPoint(cnt.points[j].x,cnt.points[j].y),20,20);
    }
    ui->label->setPixmap(pixmap);


}
