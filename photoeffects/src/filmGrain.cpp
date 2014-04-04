#include "photoeffects.hpp"

using namespace cv;
#define MAX_VALUE 20
int filmGrain(cv::InputArray src, cv::OutputArray dst)
{
    if (src.type() != CV_8UC1 && src.type() != CV_8UC3)
    {
        return 1;
    }
    Mat imageRGB=src.getMat();
    Mat imageYUV;
    cvtColor(imageRGB,imageYUV,CV_RGB2YUV);
    if(src.type()==CV_8UC1)
    {
        for(int i=0;i<imageYUV.rows;i++)
            for(int j=0;j<imageYUV.cols;j++)
            {
                int k=(imageYUV.at<uchar>(i,j)+(rand()%MAX_VALUE-rand()%MAX_VALUE));
                if(k<0)
                {
                    k=0;
                }
                if(k>=256)
                {
                    k=255;
                }
                imageYUV.at<uchar>(i,j)= k;
            }
    }
    if(src.type()==CV_8UC3)
    {
        for(int i=0;i<imageYUV.rows;i++)
            for(int j=0;j<imageYUV.cols;j++)
            {
                int k=(imageYUV.at<Vec3b>(i,j)[0]+(rand()%MAX_VALUE-rand()%MAX_VALUE));
                if(k<0)
                {
                    k=0;
                }
                if(k>=256)
                {
                    k=255;
                }
                imageYUV.at<Vec3b>(i,j)[0]= k;
            }
    }
    cvtColor(imageYUV,dst,CV_YUV2RGB);
    return 0;
}
