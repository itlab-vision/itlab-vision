#include "photoeffects.hpp"
#include <vector>
using namespace cv;
using namespace std;
int matte(InputArray src, Point topLeftCornerPoint, Point bottomRightCornerPoint, OutputArray dst)
{
    Mat srcImg = src.getMat();
    srcImg.convertTo(srcImg, CV_32FC3, 1.0f/255.0f);
    Mat bg=Mat(srcImg.size(),CV_32FC3);
    bg=Scalar(1.0f,1.0f,1.0f);
    Mat grayscale;
    cvtColor(srcImg, grayscale, COLOR_BGR2GRAY);
    int Xsize = fabs(topLeftCornerPoint.x-bottomRightCornerPoint.x);
    int Ysize = fabs(topLeftCornerPoint.y-bottomRightCornerPoint.y);
    Mat meaningPart(grayscale.rows, grayscale.cols, CV_32FC1, Scalar(0.0f,0.0f,0.0f));
    ellipse(meaningPart, Point((topLeftCornerPoint.x+Xsize/2),(topLeftCornerPoint.y+Ysize/2)), Size(Xsize/2,Ysize/2),0, 0, 360, Scalar(1.0f,1.0f,1.0f), -1, 8);
    bitwise_and(grayscale,meaningPart,meaningPart);
    Mat mask;
    meaningPart.convertTo(mask,CV_32FC1);
    threshold(1.0f-mask, mask, 0.9f, 1.0f, THRESH_BINARY_INV);
    GaussianBlur(mask, mask, Size(127, 127), 50.0f);
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