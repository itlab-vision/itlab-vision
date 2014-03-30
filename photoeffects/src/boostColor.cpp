#include "photoeffects.hpp"
#include <iostream>
using namespace cv;

int boost_color(cv::InputArray _src, float intensity, cv::OutputArray _dst)
{
	Mat src = _src.getMat();
	
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
			if(i == 0 && j == 0)
			{
				for(int k = 0; k < 3; k++)
					std::cout << srcHls.at<Vec3f>(i,j)[k] << " ";
				std::cout << std::endl;
			}
			float saturation = srcHls.at<Vec3f>(i,j)[2];
			saturation += intensity;
			if(saturation > 1.0f)
				saturation = 1.0f;
			srcHls.at<Vec3f>(i,j)[2] = saturation;
		}
	}

	_dst.create(src.size(), src.type());
	Mat dst = _dst.getMat();
	cvtColor(srcHls, dst, CV_HLS2BGR);
	
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			for(int k = 0; k < 3; k++)
				dst.at<Vec3f>(i,j)[k] *= 255.0f;
		}
	}
    return 0;
}