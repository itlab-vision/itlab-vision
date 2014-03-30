#include "photoeffects.hpp"
#include <stdlib.h>
#include <opencv2/opencv.hpp>
using namespace cv;
#define MAX_VALUE 50
int filmGrain(cv::InputArray src, cv::OutputArray dst)
{
    Mat imageRGB=src.getMat();
    Mat imageYUV;
    cvtColor(imageRGB,imageYUV,CV_RGB2YUV);
    vector<Mat> planes;
    split(imageYUV,planes);
    for(int i=0;i<imageYUV.rows;i++)
        for(int j=0;j<imageYUV.cols;j++)
        {
            int k=(planes[0].at<uchar>(i,j)+(rand()%MAX_VALUE-rand()%MAX_VALUE));
            if(k<0)
            {
                k=0;
            }
            if(k>=256)
            {
                k=255;
            }
            planes[0].at<uchar>(i,j)= k;
        }

    Mat dstYUV;
    merge(planes,dstYUV);
    cvtColor(dstYUV,dst,CV_YUV2RGB);
    return 0;
}
