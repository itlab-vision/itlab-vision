#include "photoeffects.hpp"

using namespace cv;
using namespace std;

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

    Mat image=src.getMat();
    CV_Assert(image.type() == CV_8UC1 || image.type() == CV_8UC3);
    CV_Assert(startPoint.x>=0 && startPoint.x<image.rows);
    CV_Assert(endPoint.x>=0 && endPoint.x<image.rows);
    CV_Assert(startPoint.y>=0 && startPoint.y<image.cols);
    CV_Assert(endPoint.y>=0 && endPoint.y<image.cols);
    CV_Assert(startPoint!=endPoint);
    // perpendicular to the line
    Point perpendicular;
    perpendicular.x=endPoint.x-startPoint.x;
    perpendicular.y=endPoint.y-startPoint.y;
    //line equation: A*x+By+C=0

    int A=perpendicular.y;
    int B=perpendicular.x;
    int C=-startPoint.y*A-B*startPoint.x;
    //find the most distant point from the line
    Point farthestPoint=findFarthestPoint(perpendicular, image);

    int maxDistance=abs(A*farthestPoint.x+B*farthestPoint.y+C);
    //one channel
    if(src.type() == CV_8UC1)
    {
        for(int i=0;i<image.rows;i++)
            for(int j=0;j<image.cols;j++)
            {
                int distance=A*i+B*j+C;
                //change pixels only in the direction of the perpendicular
                if(distance>0)
                {
                    int channelValue=image.at<uchar>(i,j);
                    channelValue*=(maxDistance-distance);
                    channelValue+=255*distance;
                    channelValue/=maxDistance;
                    image.at<uchar>(i,j)=channelValue;
                }
            }
        image.copyTo(dst);
        return 0;
    }

    //three channel
    for(int i=0;i<image.rows;i++)
        for(int j=0;j<image.cols;j++)
        {
            int distance=A*i+B*j+C;
            //change pixels only in the direction of the perpendicular

            if(distance>0)
            {
                for(int n=0;n<3;n++)
                {
                    int channelValue=image.at<Vec3b>(i,j)[n];
                    channelValue*=(maxDistance-distance);
                    channelValue+=255*distance;
                    channelValue/=maxDistance;
                    image.at<Vec3b>(i,j)[n]=channelValue;
                }
            }
        }
    image.copyTo(dst);
    return 0;
}
