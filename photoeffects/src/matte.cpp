#include "photoeffects.hpp"
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

Point topleftFind(Point firstPoint, Point secondPoint, int &Xsize, int &Ysize)
{
    Point topleft(0, 0);
    if(Xsize < 0)
    {
        topleft.x = firstPoint.x;
        Xsize-=(2*Xsize);
    }
    else
    {
        topleft.x = secondPoint.x;
    }
    if(Ysize < 0)
    {
        topleft.y = secondPoint.y;
        Ysize-=(2*Ysize);
    }
    else
    {
        topleft.y = firstPoint.y;
    }
    return topleft;
}

int matte(InputArray src, OutputArray dst, Point firstPoint, Point secondPoint, float sigma)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat srcImg = src.getMat();
    srcImg.convertTo(srcImg, CV_32FC3, 1.0f/255.0f);
    Mat bg=Mat(srcImg.size(),CV_32FC3);
    bg=Scalar(1.0f,1.0f,1.0f);
    int Xsize = firstPoint.x - secondPoint.x;
    int Ysize = firstPoint.y - secondPoint.y;
    Point topLeft = topleftFind(firstPoint, secondPoint, Xsize, Ysize);
    Mat meaningPart(srcImg.rows, srcImg.cols, CV_32FC1, Scalar(0.0f,0.0f,0.0f));
    ellipse(meaningPart, Point((topLeft.x+Xsize/2),(topLeft.y-Ysize/2)),
            Size(Xsize/2,Ysize/2),0, 0, 360, Scalar(1.0f,1.0f,1.0f), -1, 8);
    Mat mask;
    meaningPart.convertTo(mask,CV_32FC1);
    threshold(1.0f-mask, mask, 0.9f, 1.0f, THRESH_BINARY_INV);
    GaussianBlur(mask, mask, Size(127, 127), sigma);
    vector<Mat> ch_img;
    vector<Mat> ch_bg;
    split(srcImg,ch_img);
    split(bg, ch_bg);
    ch_img[0]=ch_img[0].mul(mask)+ch_bg[0].mul(1.0f-mask);
    ch_img[1]=ch_img[1].mul(mask)+ch_bg[1].mul(1.0f-mask);
    ch_img[2]=ch_img[2].mul(mask)+ch_bg[2].mul(1.0f-mask);
    merge(ch_img,dst);
    merge(ch_bg,bg);
    return 0;
}
