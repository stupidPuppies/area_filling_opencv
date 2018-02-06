#include "mainwindow.h"
#include <QApplication>
#include <opencv/cv.hpp>

using namespace cv;

int main(int argc, char *argv[])
{
//    Mat test = imread("../assets/images/img.jpg");
//    namedWindow("test");
//    imshow("test1", test);
//    waitKey(0);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
