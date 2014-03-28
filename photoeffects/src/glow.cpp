#include "photoeffects.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;



void apply_blend_modes(InputArray foreground, InputArray background, int blend_modes, float intensity, OutputArray result)
{
	Mat foreImg = foreground.getMat();
	Mat backImg = background.getMat();
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
				
				switch(blend_modes)
				{
					case 0: 
						intensResult = intensity * intensFore + (1 - intensity) * intensBack;
						break;
					case 1: 
						if(intensBack <= 0.5)
							intensResult = 2 * intensFore * intensBack;
						else
							intensResult = 1 - 2 * (1 - intensFore) * (1 - intensBack);
						break;
				}
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
	overlayImg.create(srcImg.size(), srcImg.type());
	apply_blend_modes(blurImg, srcImg, 1, 0.0, overlayImg);

	dst.create(srcImg.size(), srcImg.type());
	Mat dstImg;
	dstImg = dst.getMat();
	apply_blend_modes(overlayImg, srcImg, 0, intensity, dstImg);

	imwrite( "dst.jpg", dstImg );
    return 0;
}