#include "photoeffects.hpp"

using namespace cv;

Point findFarthestPoint(Point vector, Mat& image)
{
    int a,b;
    if(vector.x<=0)
    {
        a=0;
    }
    else
    {
        a=1;
    }

    if(vector.y<=0)
    {
        b=0;
    }
    else
    {
        b=1;
    }

    return Point(a*image.cols, b*image.rows);
}

int fadeColor(InputArray src, OutputArray dst,
              Point startPoint, Point endPoint)
{

    CV_Assert(!src.empty());
    Mat image=src.getMat();
    CV_Assert(image.type() == CV_8UC1 || image.type() == CV_8UC3);
    CV_Assert(startPoint.x>=0 && startPoint.x<image.cols);
    CV_Assert(endPoint.x>=0 && endPoint.x<image.cols);
    CV_Assert(startPoint.y>=0 && startPoint.y<image.rows);
    CV_Assert(endPoint.y>=0 && endPoint.y<image.rows);
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

    int maxDistance=abs(A*farthestPoint.y+B*farthestPoint.x+C);

    int numChannel=image.channels();
    dst.create(image.size(),image.type());
    Mat dstMat=dst.getMat();
    for(int i=0;i<image.rows;i++)
    {
        uchar* line( image.ptr<uchar>(i) );
        uchar* dstLine(dstMat.ptr<uchar>(i) );
        for(int j=0;j<image.cols;j++)
        {
            int distance=A*i+B*j+C;
            //change pixels only in the direction of the perpendicular
            if(distance>0)
            {

                for(int n=0;n<numChannel;n++)
                {
                    int channelValue=line[numChannel*j+n];
                    channelValue*=(maxDistance-distance);
                    channelValue+=255*distance;
                    channelValue/=maxDistance;
                    dstLine[numChannel*j+n]=channelValue;
                }
            }
        }
    }
    return 0;
}
