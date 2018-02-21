#include <QString>
#include <QtMath>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QPen>
#include <QDebug>
#include <QTimer>

#include "dragablelabel.h"

DragableLabel::DragableLabel(QWidget *parent) : QLabel(parent) {
    setMouseTracking(true);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(noMoveTimeout()));
    timer->start(TIMEOUT);
}

void DragableLabel::paintEvent(QPaintEvent *) {
         QPainter painter(this);
         if(this->pixmap())
            painter.drawPixmap(0, 0, *(this->pixmap()));
         if (needToDrawContour || imgop->IsReplaceImageEmpty()) {
             QPen pen(Qt::green,5);
             painter.setPen(pen);
             painter.setBrush(Qt::green);
             if (!imgop->IsEmpty()) {
                 for(int i=0;i<4;i++){
                     painter.drawEllipse(points[i],10,10);
                     painter.drawLine(points[ i-1 >=0 ? i-1 : 3],points[i]);
                 }
             }
         }
}

void DragableLabel::mousePressEvent(QMouseEvent *ev) {
    if (!imgop->IsEmpty()) {
        needToDrawContour = true;
        isPressing = true;
        timer->stop();
        int x=ev->x(),y=ev->y();
        //When Pressed Point
        for(int i=0;i<4;i++){
            if(qPow(points[i].x() - x,2) + qPow(points[i].y() - y,2) < 100){
                movingPointIndex = i;
                return;
            }
        }
        //When Pressed Edge
        for (int i = 0; i < 4; i++) {
            int index1 = i;
            int index2 = i == 3 ? 0 : i + 1;
            int x1 = points[index1].x();
            int y1 = points[index1].y();
            int x2 = points[index2].x();
            int y2 = points[index2].y();
            if((x1 - x) * (x2 - x) + (y1 - y) * (y2 - y) > 0)
                continue;
            double A = (y1-y2);
            double B = (x2-x1);
            double C = (x1*y2 - x2*y1);
            double dis = qAbs(A * x + B * y + C) / qSqrt(A * A + B * B);
            double k = 6;
            if(dis < k) {
                movingEdgeIndex = i;
                if (qAbs(y1 - y2) > qAbs(x1 - x2))
                    ratio = (double)(y1 - y)/(double)(y1 - y2);
                else
                    ratio = (double)(x1 - x)/(double)(x1 - x2);
                return;
            }
        }
        //When Pressed Other Area
        movingWhole = 1;
        when_moving_whole_dx_to_point0 = x - points[0].x();
        when_moving_whole_dy_to_point0 = y - points[0].y();
        update();
    }
}

void DragableLabel::mouseMoveEvent(QMouseEvent *ev) {
    qDebug() << "Moving!" << ev->x() << ev->y();
    if (!imgop->IsEmpty()) {
        needToDrawContour = true;
        timer->stop();
        if(!isPressing)
            timer->start(TIMEOUT);
        if(movingPointIndex != -1) {
            points[movingPointIndex].setX(ev->x());
            points[movingPointIndex].setY(ev->y());
        }
        if(movingEdgeIndex != -1) {
            int index1 = movingEdgeIndex;
            int index2 = movingEdgeIndex == 3 ? 0 : movingEdgeIndex + 1;
            int x1 = points[index1].x();
            int y1 = points[index1].y();
            int x2 = points[index2].x();
            int y2 = points[index2].y();
            int inital_mouse_x = x1 + ratio * (x2 - x1);
            int inital_mouse_y = y1 + ratio * (y2 - y1);
            int dx = ev->x() - inital_mouse_x;
            int dy = ev->y() - inital_mouse_y;
            points[index1].setX(x1 + dx);
            points[index1].setY(y1 + dy);
            points[index2].setX(x2 + dx);
            points[index2].setY(y2 + dy);
        }
        if (movingWhole != -1) {
            int inital_mouse_x = points[0].x() + when_moving_whole_dx_to_point0;
            int inital_mouse_y = points[0].y() + when_moving_whole_dy_to_point0;
            int dx = ev->x() - inital_mouse_x;
            int dy = ev->y() - inital_mouse_y;
            for (int i = 0; i < 4; i++) {
                points[i].setX(points[i].x() + dx);
                points[i].setY(points[i].y() + dy);
            }
        }
        imgop->CurrentSquare() = points;
        this->setPixmap(imgop->GetCanvas());
        update();
    }
}

void DragableLabel::mouseReleaseEvent(QMouseEvent *ev) {
    if (!imgop->IsEmpty()) {
        isPressing = false;
        timer->start(TIMEOUT);
        if(movingPointIndex != -1) {
            points[movingPointIndex].setX(ev->x());
            points[movingPointIndex].setY(ev->y());
            movingPointIndex = -1;
        }
        if(movingEdgeIndex != -1) {
            int index1 = movingEdgeIndex;
            int index2 = movingEdgeIndex == 3 ? 0 : movingEdgeIndex + 1;
            int x1 = points[index1].x();
            int y1 = points[index1].y();
            int x2 = points[index2].x();
            int y2 = points[index2].y();
            int inital_mouse_x = x1 + ratio * (x2 - x1);
            int inital_mouse_y = y1 + ratio * (y2 - y1);
            int dx = ev->x() - inital_mouse_x;
            int dy = ev->y() - inital_mouse_y;
            points[index1].setX(x1 + dx);
            points[index1].setY(y1 + dy);
            points[index2].setX(x2 + dx);
            points[index2].setY(y2 + dy);
            movingEdgeIndex = -1;
        }

        if (movingWhole != -1) {
            int inital_mouse_x = points[0].x() + when_moving_whole_dx_to_point0;
            int inital_mouse_y = points[0].y() + when_moving_whole_dy_to_point0;
            int dx = ev->x() - inital_mouse_x;
            int dy = ev->y() - inital_mouse_y;
            for (int i = 0; i < 4; i++) {
                points[i].setX(points[i].x() + dx);
                points[i].setY(points[i].y() + dy);
            }
            movingWhole = -1;
        }
        imgop->CurrentSquare() = points;
        this->setPixmap(imgop->GetCanvas());
        update();
    }

}

void DragableLabel::noMoveTimeout() {
    needToDrawContour = false;
    update();
}
