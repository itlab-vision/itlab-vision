#include "photoeffects.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

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
			for(int k = 0; k < 3; k++)
			{
				float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0;
				float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0;
				float intensResult = 0.0;
				
				if(intensBack <= 0.5)
					intensResult = 2 * intensFore * intensBack;
				else
					intensResult = 1 - 2 * (1 - intensFore) * (1 - intensBack);

				resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0;
			}
		}
	}
}

void opacity(InputArray foreground, InputArray background, float intensity, OutputArray result)
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
			for(int k = 0; k < 3; k++)
			{
				float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0;
				float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0;
				float intensResult = intensity * intensFore + (1 - intensity) * intensBack;
				resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0;
			}
		}
	}
}

int glow(InputArray src, unsigned int radius, float intensity, OutputArray dst)
{
	Mat srcImg = src.getMat();
	Mat blurImg;
	blurImg.create(srcImg.size(), srcImg.type());

	Size size;
	size.width = radius;
	size.height = radius;
	GaussianBlur(srcImg, blurImg, size, 0.0, 0.0);
	
	Mat overlayImg;
	//overlay(blurImg, srcImg, overlayImg);

	dst.create(srcImg.size(), srcImg.type());
	Mat dstImg;
	dstImg = dst.getMat();
	opacity(blurImg, srcImg, intensity, dstImg);

    return 0;
}