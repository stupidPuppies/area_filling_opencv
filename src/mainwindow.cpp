#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv/cv.hpp>
#include <QPainter>
#include <QPixmap>
#include <QFileDialog>
#include <vector>

#include "cannytesterwindow.h"
#include "imgoperate.h"
#include "dragablelabel.h"

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
//    imgop = ImgOperate(this);
    DragableLabel *label = new DragableLabel(this);
    ui->verticalLayout->addWidget(label);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
   QString fileName = QFileDialog::getOpenFileName(this,"Select a picture",".","JPEG Files(*.jpg);;PNG Files(*.png)");
   image = cv::imread(fileName.toStdString());
   image.copyTo(canvas);
   detectSquares();
   it = squares.begin();
   refreshCanvas();

}

void MainWindow::on_nextButton_clicked()
{
    image.copyTo(canvas);
    if (it == squares.end()) return;
    cv::drawContours(canvas, squares, distance(squares.begin(), it), cv::Scalar(0, 255, 0), 5, 8, std::vector<cv::Vec4i>(), 0, cv::Point());
    it++;
    if (it == squares.end()) it = squares.begin();
    refreshCanvas();
}

void MainWindow::refreshCanvas() {
    cv::cvtColor(canvas,canvas_output, CV_BGR2RGB);
    ui->label->setPixmap(
                QPixmap::fromImage(
                    QImage(
                        canvas_output.data,
                        canvas_output.cols,
                        canvas_output.rows,
                        canvas_output.step,
                        QImage::Format_RGB888
                        )
                    )
                );
}

void MainWindow::detectSquares() {
    vector<vector<cv::Point>> contours;
    Mat blurred(image.size(), CV_8UC3);
    medianBlur(image, blurred, 9);
    Mat gray0(blurred.size(), CV_8U), gray;
    for (int c = 0; c < 3; c++) {
        int ch[] = { c, 0 };
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++) {
            if (l == 0) {
                Canny(gray0, gray, 10, 20, 3);
                dilate(gray, gray, Mat(), Point(-1, -1));
            } else {
                gray = gray0 >= (l + 1) * 255 / threshold_level;
            }

            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++) {
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
                if (approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx))) {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++) {
                        double cosine = fabs(angle(approx[j % 4], approx[j - 2], approx[j - 1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if (maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    CannyTesterWindow *ctw = new CannyTesterWindow;
    ctw->show();
    this->hide();
}
