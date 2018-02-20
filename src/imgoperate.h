#ifndef IMGOPERATE_H
#define IMGOPERATE_H

#include <QString>
#include <QPoint>
#include <QPixmap>

#include <opencv/cv.hpp>
#include <vector>

typedef std::vector<QPoint> Square;

class ImgOperate
{
public:
    ImgOperate();
    Square& CurrentSquare();
    const Square& CurrentSquare() const;
    Square NextSquare();
    Square PreviousSquare();
    int LoadMainImage(QString fileName);
    int LoadReplaceImage(QString fileName);
    QPixmap GetCanvas();
    int SaveImage(QString fileName);
    bool IsEmpty();

private:
    cv::Mat main_image;
    cv::Mat canvas;
    cv::Mat canvas_output;
    cv::Mat replace_image;
    cv::Mat replace_image_transformed;
    std::vector<Square> squares;
    std::vector<Square>::iterator it;
    Square current_square;

    void initialize();
    int loadImage(QString fileName, cv::Mat& mat);
    void detectSquares();
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
    int process();
    int refreshCanvas();
    int replace();
};

#endif // IMGOPERATE_H
