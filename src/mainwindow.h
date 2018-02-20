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
private slots:
    void on_loadButton_clicked();

    void on_nextButton_clicked();

    void on_pushButton_clicked();

    void on_replaceButton_clicked();

    void on_prevButton_clicked();

    void on_saveButton_clicked();

private:
    ImgOperate imgop;
    Ui::MainWindow *ui;
    DragableLabel *label;
};

#endif // MAINWINDOW_H
