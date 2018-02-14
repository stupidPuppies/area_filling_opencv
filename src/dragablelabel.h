#ifndef dragABLELABEL_H
#define dragABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
class DragableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragableLabel(QWidget *parent = nullptr);
    QPoint points[4];
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
private:
    int movingPointIndex = -1;
signals:

public slots:
};

#endif // dragABLELABEL_H
