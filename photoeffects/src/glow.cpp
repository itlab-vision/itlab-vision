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

		Mat resultImg2(backImg.size(), CV_32SC1); 

		backImg.convertTo(backImg, CV_32SC3);
		backImg = backImg.reshape(1);
		foreImg.convertTo(foreImg, CV_32SC3);	
		foreImg = foreImg.reshape(1);
		
		Mat tmp;
		TIMER_START(slow);
		cv::multiply(foreImg, backImg, tmp, 2); 
		tmp /= 255;
		Mat mask = backImg > 127;
		cv::add(-tmp, 2 * (foreImg + backImg) - 255, resultImg2, mask);
		cv::add(tmp, 0, resultImg2, ~mask);
		TIMER_END(slow);
		resultImg2 = resultImg2.reshape(3);
		backImg = backImg.reshape(3);
		backImg.convertTo(backImg, CV_8UC3);
		resultImg2.convertTo(resultImg2, CV_8UC3);

		resultImg2.copyTo(resultImg);
    }

	
    void overlay3(InputArray foreground, InputArray background, OutputArray result)
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
                    uchar intensFore = foreImg.at<Vec3b>(i, j)[k];
                    uchar intensBack = backImg.at<Vec3b>(i, j)[k];
					int intensResult = (2 * intensFore * intensBack) / 255;
                    
                    if (intensBack > 127)
                    {
                        intensResult = cv::min(-intensResult - 255 +2 * (intensFore + intensBack), 255);
                    }
					resultImg.at<Vec3b>(i, j)[k] = intensResult;
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
    if (srcImgType != CV_8UC3)
    {
        srcImg.convertTo(srcImg, CV_8UC3);
    }

    Mat blurImg;
    Size size(radius, radius);
    GaussianBlur(srcImg, blurImg, size, 0.0f, 0.0f);
    Mat overlayImg;
    overlay3(blurImg, srcImg, overlayImg);
	/*
	blurImg.convertTo(blurImg, CV_32FC3);
	srcImg.convertTo(srcImg, CV_32FC3);
	Mat overlayImg2;
    overlay(blurImg, srcImg, overlayImg2);
	blurImg.convertTo(blurImg, CV_8UC3);
	srcImg.convertTo(srcImg, CV_8UC3);
	overlayImg2.convertTo(overlayImg2, CV_8UC3);
	Mat diff = abs(overlayImg2 - overlayImg);
	diff = diff.reshape(1);
	Mat mask = diff > 1;
	printf("%d\n", cv::countNonZero(mask));
	*/

	uchar coeff = static_cast<uchar>(intensity * 256.0 + 0.5);
	Mat dstImg = (coeff * overlayImg + (256 - coeff) * srcImg) / 256; 
    //opacity(overlayImg, srcImg, dst, intensity);
    dstImg.convertTo(dst, srcImgType);
    return 0;
}