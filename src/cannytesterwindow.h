#ifndef CANNYTESTERWINDOW_H
#define CANNYTESTERWINDOW_H
#include <opencv/cv.hpp>
#include <QMainWindow>

namespace Ui {
class CannyTesterWindow;
}

class CannyTesterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CannyTesterWindow(QWidget *parent = 0);
    ~CannyTesterWindow();
    cv::Mat image;

private slots:
    void on_low_sliderMoved(int position);

    void on_ratio_sliderMoved(int position);

    void on_ksize_sliderMoved(int position);

    void on_action_load();

    void on_action_triggered();

private:
    Ui::CannyTesterWindow *ui;
};

#endif // CANNYTESTERWINDOW_H
