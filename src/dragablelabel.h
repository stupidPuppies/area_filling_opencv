#ifndef dragABLELABEL_H
#define dragABLELABEL_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <vector>

#include <opencv/cv.hpp>



class DragableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit DragableLabel(QWidget *parent = nullptr);
    QPoint points[4] = {QPoint(10,10),QPoint(100,10),QPoint(100,100),QPoint(10,100)};
    std::vector<std::vector<cv::Point> > squares;
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
