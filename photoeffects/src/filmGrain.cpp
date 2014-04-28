#include "photoeffects.hpp"

using namespace cv;
int filmGrain(InputArray src, OutputArray dst, int grainValue)
{
    CV_Assert(!src.empty());
    CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3);

    Mat image=src.getMat();

    RNG& rng=theRNG();
    if(src.type()==CV_8UC1)
    {
        for(int i=0; i<image.rows; i++)
            for(int j=0; j<image.cols; j++)
            {
                int newValue=(image.at<uchar>(i, j)+rng.gaussian(grainValue));
                if(newValue<0)
                {
                    newValue=0;
                }
                if(newValue>=256)
                {
                    newValue=255;
                }
                image.at<uchar>(i, j)= newValue;
            }
        image.copyTo(dst);
    }
    if(src.type()==CV_8UC3)
    {
        Mat imageYUV;
        cvtColor(image, imageYUV, CV_RGB2YUV);
        for(int i=0; i<imageYUV.rows; i++)
            for(int j=0; j<imageYUV.cols; j++)
            {
                int newValue=(imageYUV.at<Vec3b>(i, j)[0]+rng.gaussian(grainValue));
                if(newValue<0)
                {
                    newValue=0;
                }
                if(newValue>=256)
                {
                    newValue=255;
                }
                imageYUV.at<Vec3b>(i, j)[0]= newValue;
            }
        cvtColor(imageYUV, dst, CV_YUV2RGB);
    }
    return 0;
}
