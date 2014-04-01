#include "photoeffects.hpp"

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
				float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0f;
				float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0f;
				float intensResult = 0.0f;
				
				if(intensBack <= 0.5f)
					intensResult = 2.0f * intensFore * intensBack;
				else
					intensResult = 1.0f - 2.0f * (1.0f - intensFore) * (1.0f - intensBack);

				resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0f;
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
	float intensityReverse = 1 - intensity;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				float intensFore = foreImg.at<Vec3f>(i, j)[k] / 255.0f;
				float intensBack = backImg.at<Vec3f>(i, j)[k] / 255.0f;
				float intensResult = intensity * intensFore + intensityReverse * intensBack;
				resultImg.at<Vec3f>(i,j)[k] = intensResult * 255.0f;
			}
		}
	}
}

// 1 - not 3-channel image
// 2 - bad radius
// 3 - bad intensity

int glow(InputArray src, float radius, float intensity, OutputArray dst)
{
	Mat srcImg = src.getMat();

	if(srcImg.channels() != 3)
	{
		return 1;
	}
	if(radius < 0.0f)
	{
		return 2;
	}
	if(intensity < 0.0f || intensity > 1.0f)
	{
		return 3;
	}

	Mat blurImg;
	blurImg.create(srcImg.size(), srcImg.type());

	Size size;
	size.width = 0.0f;
	size.height = 0.0f;
	GaussianBlur(srcImg, blurImg, size, radius, radius);
	
	Mat overlayImg;
	overlay(blurImg, srcImg, overlayImg);

	dst.create(srcImg.size(), srcImg.type());
	Mat dstImg;
	dstImg = dst.getMat();
	opacity(overlayImg, srcImg, intensity, dstImg);

    return 0;
}