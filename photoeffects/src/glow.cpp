#include "photoeffects.hpp"

using namespace cv;

#include <stdio.h>
#define TIMER_START(name) int64 t_##name = getTickCount()
#define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
            1000.f * ((getTickCount() - t_##name) / getTickFrequency()))


namespace
{
    const int COUNT_CHANNEL = 3;

    void overlay2(InputArray foreground, InputArray background, OutputArray result)
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

int glow(InputArray src, OutputArray dst, int radius, float intensity)
{
    Mat srcImg = src.getMat();

    CV_Assert(srcImg.channels() == COUNT_CHANNEL);
    CV_Assert(radius >= 0 && radius % 2 != 0);
    CV_Assert(intensity >= 0.0f && intensity <= 1.0f);

    int srcImgType = srcImg.type();
    if (srcImgType != CV_32FC3)
    {
		TIMER_START(to32f);
        srcImg.convertTo(srcImg, CV_32FC3);
		TIMER_END(to32f);
    }

    Mat blurImg;
    Size size(radius, radius);
	TIMER_START(blur);
    GaussianBlur(srcImg, blurImg, size, 0.0f, 0.0f);
	TIMER_END(blur);
    Mat overlayImg;
	TIMER_START(overl);
    overlay(blurImg, srcImg, overlayImg);
	TIMER_END(overl);
	overlayImg.convertTo(overlayImg, CV_8UC3);
	srcImg.convertTo(srcImg, CV_8UC3);
	TIMER_START(opac);
	uchar coeff = static_cast<uchar>(intensity * 256.0 + 0.5);
	Mat dstImg = (coeff * overlayImg - (256 - coeff) * srcImg) / 256; 
    //opacity(overlayImg, srcImg, dst, intensity);
	TIMER_END(opac);
    //Mat dstImg = dst.getMat();
    TIMER_START(toSrcType);
    dstImg.convertTo(dst, srcImgType);
    TIMER_END(toSrcType);
    return 0;
}