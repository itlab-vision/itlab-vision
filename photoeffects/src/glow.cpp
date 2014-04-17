#include "photoeffects.hpp"

using namespace cv;

namespace
{
    const int COUNT_CHANNEL = 3;

    void overlay(InputArray foreground, InputArray background, OutputArray result)
    {
        Mat foreImg = foreground.getMat();
        Mat backImg = background.getMat();

        result.create(backImg.size(), backImg.type());
        Mat resultImg = result.getMat();

        int width = foreImg.cols;
        int height = foreImg.rows;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                for(int k = 0; k < COUNT_CHANNEL; k++)
                {
                    float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0f;
                    float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0f;
                    float intensResult = 2.0f * intensFore * intensBack;
                    
                    if (intensBack > 0.5f)
                    {
                        intensResult = -intensResult - 1.0f + 2.0f * (intensFore + intensBack);
                    }
    
                    resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0f;
                }
            }
        }
    }

    void opacity(InputArray foreground, InputArray background, OutputArray result, float intensity)
    {
        Mat foreImg = foreground.getMat();
        Mat backImg = background.getMat();

        result.create(backImg.size(), backImg.type());
        Mat resultImg = result.getMat();

        int width = foreImg.cols;
        int height = foreImg.rows;
        float intensityReverse = 1.0f - intensity;
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                for(int k = 0; k < COUNT_CHANNEL; k++)
                {
                    float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0f;
                    float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0f;
                    float intensResult = intensity * intensFore + intensityReverse * intensBack;
                    resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0f;
                }
            }
        }
    }
}   

int glow(InputArray src, OutputArray dst, float sigma, float intensity)
{
    Mat srcImg = src.getMat();

    CV_Assert(srcImg.channels() == COUNT_CHANNEL);
    CV_Assert(sigma > 0.0f);
    CV_Assert(intensity >= 0.0f && intensity <= 1.0f);

    int srcImgType = srcImg.type();
    if (srcImgType != CV_32FC3)
    {
        srcImg.convertTo(srcImg, CV_32FC3);
    }

    Mat blurImg;
    Size size(0, 0);

    GaussianBlur(srcImg, blurImg, size, sigma, sigma);
 
    Mat overlayImg;
    overlay(blurImg, srcImg, overlayImg);

    opacity(overlayImg, srcImg, dst, intensity);
    Mat dstImg = dst.getMat();
    
    dstImg.convertTo(dst, srcImgType);
    
    return 0;
}