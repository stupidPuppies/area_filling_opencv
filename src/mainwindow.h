#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imgoperate.h>
#include <opencv/cv.hpp>
#include <vector>

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

private slots:
    void on_loadButton_clicked();

    void on_nextButton_clicked();

private:
    ImgOperate imgop;
    cv::Mat image;
    cv::Mat canvas;
    cv::Mat canvas_output;
    vector<vector<cv::Point> > squares;
    Ui::MainWindow *ui;
    vector<vector<cv::Point> >::iterator it;

    void refreshCanvas();
    void detectSquares();
};

#endif // MAINWINDOW_H
