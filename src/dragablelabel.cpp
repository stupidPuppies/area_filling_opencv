#include "dragablelabel.h"
#include <QString>
#include <QtMath>
DragableLabel::DragableLabel(QWidget *parent) : QLabel(parent)
{

}

void DragableLabel::mousePressEvent(QMouseEvent *ev)
{
    int x=ev->x(),y=ev->y();
    for(int i=0;i<4;i++){
        if(qPow(points[i].x() - x,2) + qPow(points[i].y() - y,2) < 100){
            movingPointIndex = i;
            return;
        }
    }
}

void DragableLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(movingPointIndex != -1) {
        points[movingPointIndex].setX(ev->x());
        points[movingPointIndex].setY(ev->y());
    }
}

void DragableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(movingPointIndex != -1) {
        points[movingPointIndex].setX(ev->x());
        points[movingPointIndex].setY(ev->y());
        movingPointIndex = -1;
    }
}

