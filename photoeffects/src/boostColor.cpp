#include "photoeffects.hpp"
#include <iostream>
using namespace cv;

//1 - bad image
//2 - bad intensity

int boost_color(cv::InputArray _src, cv::OutputArray _dst, float intensity)
{
	Mat src = _src.getMat();

	if(src.channels() != 3)
		return 1;
	if(intensity < 0.0f || intensity > 1.0f)
		return 2;
	
	src.convertTo(src, CV_32FC3);

	int height = src.rows;
	int width = src.cols;

	Mat srcHls(src);
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			for(int k = 0; k < 3; k++)
				srcHls.at<Vec3f>(i,j)[k] /= 255.0f;
		}
	}
	cvtColor(srcHls, srcHls, CV_BGR2HLS);

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			//increase channel - 3(saturation)
			float saturation = srcHls.at<Vec3f>(i,j)[2];
			saturation += intensity;
			if(saturation > 1.0f)
				saturation = 1.0f;
			srcHls.at<Vec3f>(i,j)[2] = saturation;
		}
	}

	Mat dst;
	cvtColor(srcHls, dst, CV_HLS2BGR);
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			for(int k = 0; k < 3; k++)
				dst.at<Vec3f>(i,j)[k] *= 255.0f;
		}
	}
	dst.convertTo(_dst, CV_8UC3);
	
    return 0;
}