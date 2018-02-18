#include "dragablelabel.h"
#include <QString>
#include <QtMath>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QPen>
DragableLabel::DragableLabel(QWidget *parent) : QLabel(parent)
{

}

void DragableLabel::paintEvent(QPaintEvent *)
{


         QPainter painter(this);
         QPen pen(Qt::red,1);
         painter.setPen(pen);
         painter.setBrush(Qt::red);
         for(int i=0;i<4;i++){
             painter.drawEllipse(points[i],10,10);
             painter.drawLine(points[ i-1 >=0 ? i-1 : 3],points[i]);
         }
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
    update();
}

void DragableLabel::mouseMoveEvent(QMouseEvent *ev)
{
    if(movingPointIndex != -1) {
        points[movingPointIndex].setX(ev->x());
        points[movingPointIndex].setY(ev->y());
    }
    update();
}
void DragableLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if(movingPointIndex != -1) {
        points[movingPointIndex].setX(ev->x());
        points[movingPointIndex].setY(ev->y());
        movingPointIndex = -1;
    }
    update();
}

