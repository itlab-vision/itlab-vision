#include "photoeffects.hpp"
#include <math.h>
using namespace cv;

int fadeColor(InputArray src, OutputArray dst,cv::Point startPoint,cv::Point endPoint)
{
    Mat image=src.getMat();
    Point vector,newPoint ;
    // perpendicular to the line
    vector.x=-(startPoint.x-endPoint.x);
    vector.y=-(startPoint.y-endPoint.y);
    //second point of the line
    newPoint.x=startPoint.x+vector.y;
    newPoint.y=startPoint.y-vector.x;
    //line equation: A*x+By+C=0

    int A=(startPoint.x-newPoint.x);
    int B=-(startPoint.y-newPoint.y);
    int C=-startPoint.y*A-B*startPoint.x;

    //find the most distant point from the line
    Point farthestPoint;
    if(vector.x<=0 && vector.y<=0)
    {
        farthestPoint=Point(0,0);
    }
    else
    {
        if(vector.x<=0 && vector.y>0)
        {
            farthestPoint=Point(image.rows,0);
        }
        else
        {
            if(vector.x>0 && vector.y<=0)
            {
                farthestPoint=Point(0,image.cols);
            }
            else
            {
                if(vector.x>0 && vector.y>0)
                {
                    farthestPoint=Point(image.rows,image.cols);
                }
            }
        }
    }

    double maximumDistance=abs(A*farthestPoint.x+B*farthestPoint.y+C);
    for(int i=0;i<image.rows;i++)
        for(int j=0;j<image.cols;j++)
        {
            double distance=abs(A*i+B*j+C);
            //change pixels only in the direction of the perpendicular
            if((vector.x*(j-startPoint.x)+vector.y*(i-startPoint.y))>=0)
            {
                 image.at<uchar>(i,j)=(image.at<uchar>(i,j)*(maximumDistance-distance)+255*distance)/maximumDistance;
            }
        }
    image.copyTo(dst);
    return 0;
}
