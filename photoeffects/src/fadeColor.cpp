#include "photoeffects.hpp"
#include <math.h>
#include <vector>

using namespace cv;
using namespace std;

double scalarProduct(Point a, Point b)
{
    return a.x*b.x+a.y*b.y;
}

Point findFarthestPoint(Point vector, Mat& image)
{
    Point farthestPoint;
    if(vector.x<=0 && vector.y<=0)
    {
        farthestPoint=Point(0, 0);
    }

    if(vector.x<=0 && vector.y>0)
    {
        farthestPoint=Point(image.rows, 0);
    }

    if(vector.x>0 && vector.y<=0)
    {
        farthestPoint=Point(0, image.cols);
    }

    if(vector.x>0 && vector.y>0)
    {
        farthestPoint=Point(image.rows, image.cols);
    }

    return farthestPoint;
}

int fadeColor(InputArray src, OutputArray dst,
              Point startPoint, Point endPoint)
{
    if (src.type() != CV_8UC1 && src.type() != CV_8UC3)
    {
        return 1;
    }
    Mat image=src.getMat();
    Point perpendicular;
    // perpendicular to the line

    perpendicular.x=endPoint.x-startPoint.x;
    perpendicular.y=endPoint.y-startPoint.y;
    //line equation: A*x+By+C=0

    int A=-perpendicular.y;
    int B=-perpendicular.x;
    int C=-startPoint.y*A-B*startPoint.x;

    //find the most distant point from the line
    Point farthestPoint=findFarthestPoint(perpendicular, image);


    int maxDistance=abs(A*farthestPoint.x+B*farthestPoint.y+C);
    vector<Mat> planes;
    split(image,planes);
    for(int i=0;i<image.rows;i++)
        for(int j=0;j<image.cols;j++)
        {
            int distance=abs(A*i+B*j+C);
            //change pixels only in the direction of the perpendicular
            Point directionVector(j-startPoint.x, i-startPoint.y);
            if(scalarProduct(perpendicular, directionVector)>=0)
            {
                for(int n=0;n<image.channels();n++)
                {
                    int channelValue=planes[n].at<uchar>(i,j);
                    channelValue*=(maxDistance-distance);
                    channelValue+=255*distance;
                    channelValue/=maxDistance;
                    planes[n].at<uchar>(i,j)=channelValue;
                }
            }
        }

    merge(planes, dst);
    return 0;
}
