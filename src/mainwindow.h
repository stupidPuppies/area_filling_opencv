    #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <imgoperate.h>
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

private:
    ImgOperate imgop;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
