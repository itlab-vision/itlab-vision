#include "photoeffects.hpp"
#include <math.h>
#include <vector>
using namespace cv;
using namespace std;
Point findFarthestPoint(Point vector,Mat& image)
{
    if(vector.x<=0 && vector.y<=0)
    {
        return Point(0,0);
    }

    if(vector.x<=0 && vector.y>0)
    {
        return Point(image.rows,0);
    }

    if(vector.x>0 && vector.y<=0)
    {
        return Point(0,image.cols);
    }

    if(vector.x>0 && vector.y>0)
    {
        return Point(image.rows,image.cols);
    }
}

int fadeColor(InputArray src, OutputArray dst,Point startPoint,Point endPoint)
{
    Mat image=src.getMat();
    Point perpendicular,newPoint ;
    // perpendicular to the line
    perpendicular.x=-(startPoint.x-endPoint.x);
    perpendicular.y=-(startPoint.y-endPoint.y);
    //second point of the line
    newPoint.x=startPoint.x+perpendicular.y;
    newPoint.y=startPoint.y-perpendicular.x;
    //line equation: A*x+By+C=0

    int A=(startPoint.x-newPoint.x);
    int B=-(startPoint.y-newPoint.y);
    int C=-startPoint.y*A-B*startPoint.x;

    //find the most distant point from the line
    Point farthestPoint=findFarthestPoint(perpendicular,image);


    int maximumDistance=abs(A*farthestPoint.x+B*farthestPoint.y+C);
    vector<Mat> planes;
    split(image,planes);
    for(int i=0;i<image.rows;i++)
        for(int j=0;j<image.cols;j++)
        {
            double distance=abs(A*i+B*j+C);
            //change pixels only in the direction of the perpendicular
            if((perpendicular.x*(j-startPoint.x)+perpendicular.y*(i-startPoint.y))>=0)
            {
                for(int n=0;n<image.channels();n++)
                {
                 planes[n].at<uchar>(i,j)=(planes[n].at<uchar>(i,j)*(maximumDistance-distance)+255*distance)/maximumDistance;
                }
            }
        }

    merge(planes,dst);
    return 0;
}
