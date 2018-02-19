#include "cannytesterwindow.h"
#include "ui_cannytesterwindow.h"
#include "opencv/cv.hpp"
#include <QFileDialog>
CannyTesterWindow::CannyTesterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CannyTesterWindow)
{
    ui->setupUi(this);
}

CannyTesterWindow::~CannyTesterWindow()
{
    delete ui;
}

void CannyTesterWindow::on_low_sliderMoved(int position)
{
    int lowThreshold = ui->low->value();
    int highThreshold = ui->ratio->value() * lowThreshold;
    int ksize = ui->ksize->value();
    ui->label_2->setText(QString::number(lowThreshold)+"\t"+QString::number(highThreshold)+"\t"+QString::number(ksize));
    if(ksize % 2 ==0) ksize++;

    cv::Mat temp,edged;
    cv::GaussianBlur(this->image, temp, cv::Size(ksize,ksize), 0, 0);
    cv::Canny(temp,edged,lowThreshold,highThreshold);
//    cv::cvtColor(edges, edges, CV_BGR2RGB);
    QPixmap pixmap = QPixmap::fromImage(QImage(edged.data, edged.cols, edged.rows, edged.step, QImage::Format_Grayscale8));
    ui->label->setPixmap(pixmap);
}

void CannyTesterWindow::on_ratio_sliderMoved(int position)
{
    this->on_low_sliderMoved(0);
}

void CannyTesterWindow::on_ksize_sliderMoved(int position)
{
    this->on_low_sliderMoved(0);
}

void CannyTesterWindow::on_action_load()
{

}

void CannyTesterWindow::on_action_triggered()
{
    this->image = cv::imread((QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)")).toStdString());
    this->on_low_sliderMoved(0);
}
