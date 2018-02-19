#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imgoperate.h>
#include <opencv/cv.hpp>
#include <vector>

#include "dragablelabel.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void replace();
    void refreshCanvas();
private slots:
    void on_loadButton_clicked();

    void on_nextButton_clicked();

    void on_pushButton_clicked();

    void on_replaceButton_clicked();

private:
    ImgOperate imgop;
    cv::Mat image;
    cv::Mat canvas;
    cv::Mat canvas_output;
    cv::Mat replace_image;
    cv::Mat replace_image_transformed;
    vector<vector<cv::Point> > squares;
    Ui::MainWindow *ui;
    vector<vector<cv::Point>>::iterator it;
    DragableLabel *label;

    void detectSquares();

};

#endif // MAINWINDOW_H
