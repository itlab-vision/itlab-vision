#include "photoeffects.hpp"
#include <vector>

using namespace cv;
using namespace std;

Point topleftFind(Point firstPoint, Point secondPoint, int &xsize, int &ysize)
{
    Point topleft(0, 0);
    if(xsize < 0)
    {
        topleft.x = firstPoint.x;
        xsize-=(2*xsize);
    }
    else
    {
        topleft.x = secondPoint.x;
    }
    if(ysize < 0)
    {
        topleft.y = secondPoint.y;
        ysize-=(2*ysize);
    }
    else
    {
        topleft.y = firstPoint.y;
    }
    return topleft;
}

int matte(InputArray src, OutputArray dst, Point firstPoint, Point secondPoint, float sigma)
{
    CV_Assert((src.type() == CV_8UC3) || (src.type() == CV_32FC3));
    Mat srcImg = src.getMat();
    if(srcImg.type() != CV_32FC3)
    {
        srcImg.convertTo(srcImg, CV_32FC3, 1.0f/255.0f);
    }
    Mat bg=Mat(srcImg.size(),CV_32FC3);
    bg=Scalar(1.0f,1.0f,1.0f);
    int xsize = firstPoint.x - secondPoint.x;
    int ysize = firstPoint.y - secondPoint.y;
    Point topLeft = topleftFind(firstPoint, secondPoint, xsize, ysize);
    Mat mask(srcImg.rows, srcImg.cols, CV_32FC1, Scalar(0.0f,0.0f,0.0f));
    ellipse(mask, Point((topLeft.x+xsize/2),(topLeft.y-ysize/2)),
            Size(xsize/2,ysize/2),0, 0, 360, Scalar(1.0f,1.0f,1.0f), -1, 8);
    GaussianBlur(mask, mask, Size(127, 127), sigma);
    vector<Mat> ch_img;
    vector<Mat> ch_bg;
    split(srcImg,ch_img);
    split(bg, ch_bg);
    ch_img[0]=ch_img[0].mul(mask)+ch_bg[0].mul(1.0f-mask);
    ch_img[1]=ch_img[1].mul(mask)+ch_bg[1].mul(1.0f-mask);
    ch_img[2]=ch_img[2].mul(mask)+ch_bg[2].mul(1.0f-mask);
    merge(ch_img,dst);
    return 0;
}
