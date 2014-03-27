#include "photoeffects.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

int glow(cv::InputArray src, unsigned int radius, float intensity, cv::OutputArray dst)
{
	Mat srcImg = src.getMat();
	Mat blurSrc;
	blurSrc.create(srcImg.size(), srcImg.type());
	Size size;
	size.width = radius;
	size.height = radius;
	GaussianBlur(srcImg, blurSrc, size, 0.0, 0.0);
	imwrite( "blur.jpg", blurSrc );
	dst.create(srcImg.size(), srcImg.type());
	Mat dstImg;
	dstImg = dst.getMat();
	for(int i = 0; i < srcImg.rows; i++)
	{
		for(int j = 0; j < srcImg.cols; j++)
		{
			for(int k = 0; k < 3; k++)
			{
				float intensSrc = srcImg.at<Vec3f>(i, j)[k] / 255.0;
				float intensBlur = blurSrc.at<Vec3f>(i, j)[k] / 255.0;
				float intensDst = 0.0;
				if(intensSrc <= 0.5)
					intensDst = (2 * intensSrc - 1) * (intensBlur - intensBlur * intensBlur) + intensBlur;
				else
					intensDst = (2 * intensSrc - 1) * (sqrt(intensBlur) - intensBlur) + intensBlur;
				dstImg.at<Vec3f>(i,j)[k] = intensDst * 255.0;
			}
		}
	}
	imwrite( "dst.jpg", dstImg );
    return 0;
}