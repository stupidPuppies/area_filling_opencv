#include "imgoperate.h"
#include <vector>
#include <algorithm>
using namespace std;


ImgOperate::ImgOperate(QObject *parent) : QObject(parent)
{

}

bool ImgOperate::loagImg(QString path)
{
    this->img = cv::imread(path.toStdString());
    if(this->img.data == NULL) return false;
    return true;
}

bool ImgOperate::process()
{
    Mat edges;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    Canny(this->img,edges,100,200);
    findContours(edges,contours,hierarchy,RETR_LIST,CHAIN_APPROX_SIMPLE);

    for(int i=0;i<contours.size();i++){
        struct CntInfo cnt;
        vector<Point> approx,contour = contours[i];

        double peri = arcLength(contour,true);
        approxPolyDP(contour,approx,0.02 * peri,true);

        if(approx.size() != 4) continue;

        for(int j=0;j<approx.size();j++)
            cnt.points[j] = approx[j];
        cnt.area = contourArea(contour,true);

        cnts.push_back(cnt);
    }

    std::sort(cnts.begin(),cnts.end(),[](const struct CntInfo &a,const struct CntInfo &b){return a.area > b.area;});

    return true;

}

ImgOperate::~ImgOperate()
{

}
