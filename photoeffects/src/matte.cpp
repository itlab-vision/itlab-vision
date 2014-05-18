#include "photoeffects.hpp"
#include <iostream>

using namespace cv;
using namespace std;

namespace
{
    Point topleftFind(Point firstPoint, Point secondPoint, float &xsize, float &ysize)
    {
        Point topleft(0, 0);
        if(xsize < 0)
        {
            topleft.x = firstPoint.x;
            xsize = -xsize;
        }
        else
        {
            topleft.x = secondPoint.x;
        }
        if(ysize < 0)
        {
            topleft.y = secondPoint.y;
            ysize = -ysize;
        }
        else
        {
            topleft.y = firstPoint.y;
        }
        return topleft;
    }
}

int matte(InputArray src, OutputArray dst, Point firstPoint, Point secondPoint)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat srcImg = src.getMat();
    CV_Assert(!(srcImg.empty()));
    double t = (double)getTickCount();
    float xsize = firstPoint.x - secondPoint.x;
    float ysize = firstPoint.y - secondPoint.y;
    Point topLeft = topleftFind(firstPoint, secondPoint, xsize, ysize);
    float aSquare = xsize*xsize/4.0f;
    float bSquare = ysize*ysize/4.0f;
    float xellipseCenter = topLeft.x + xsize/2.0f;
    float yellipseCenter = topLeft.y - ysize/2.0f;
    float aSQ = srcImg.cols*srcImg.cols/4.0f;
    float bSQ = srcImg.rows*srcImg.rows/4.0f;
    float coef = 0;
    const Vec3b whiteIntensity(255, 255, 255);
    Vec3b currentIntensity;
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Preparations : "<<t*1000<<"ms"<<endl;
    t = (double)getTickCount();
    for (int i = 0; i < srcImg.rows; i++)
    {
        float ijCenterX= i - yellipseCenter;
        float ijCenterXSquare = ijCenterX*ijCenterX;
        for(int j = 0; j < srcImg.cols; j++)
        {
            currentIntensity = srcImg.at<Vec3b>(i,j);
            float ijCenterY = j - xellipseCenter;
            float ijCenterYSquare = ijCenterY*ijCenterY;
            float destin = ijCenterXSquare/bSquare + ijCenterYSquare/aSquare;
            if(destin > 1.0f)
            {
                float denominator =(ijCenterXSquare/bSQ + ijCenterYSquare/aSQ)*destin;
                float alpha= 1.0f/denominator;
                if(alpha > 1.0f)
                {
                    alpha = 1.0f;
                }
                coef = 1.0f - alpha;
                dst.getMat().at<Vec3b>(i,j) = alpha*currentIntensity + coef*whiteIntensity;
            }
        }
    }
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "Cicle : "<<t*1000<<"ms"<<endl;
    return 0;
}
