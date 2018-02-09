#ifndef IMGOPERATE_H
#define IMGOPERATE_H

#include <QObject>
#include <QVector>
#include <QPoint>
#include <QString>
#include <opencv/cv.hpp>
using namespace cv;

struct CntInfo{
    int area;
    Point points[4];
};

class ImgOperate : public QObject
{
    Q_OBJECT
public:
//    QVector<QPoint[4]> edgePoints;
    QVector<struct CntInfo> cnts;
    Mat img;
    explicit ImgOperate(QObject *parent = nullptr);
    bool loagImg(QString path);
    bool process();
    ~ImgOperate();
private:


signals:

public slots:
};

#endif // IMGOPERATE_H
