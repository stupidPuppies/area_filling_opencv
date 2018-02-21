#ifndef dragABLELABEL_H
#define dragABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QTimer>
#include <vector>
#include <opencv/cv.hpp>

#include "imgoperate.h"


#define TIMEOUT 2000

class DragableLabel : public QLabel {
    Q_OBJECT
public:
    explicit DragableLabel(QWidget *parent = nullptr);
    Square points = {QPoint(10,10), QPoint(100,10), QPoint(100,100), QPoint(10,100)};
    ImgOperate *imgop;
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    int movingPointIndex = -1;
    int movingEdgeIndex = -1;
    int movingWhole = -1;
    int when_moving_whole_dx_to_point0;
    int when_moving_whole_dy_to_point0;
    double ratio;
    QTimer *timer;
    bool isPressing = false;
    bool needToDrawContour = true;
signals:

public slots:
    void noMoveTimeout();

};

#endif // dragABLELABEL_H
