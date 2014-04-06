#include "photoeffects.hpp"
#include <iostream>

using namespace cv;

void RgbToHsl(const Vec3f &rgb, Vec3f &hsl)
{
	float min, max, delta;

	Vec3f rgbNorm = rgb;
	for(int i = 0; i < 3; i++)
		rgbNorm[i] /= 255.0f;

	min = max = rgbNorm[0];
	for(int i = 1; i < 3; i++)
	{
		if(min > rgbNorm[i])
			min = rgbNorm[i];
		if(max < rgbNorm[i])
			max = rgbNorm[i];
	}

	delta = max - min;
	//h
	if(max == min)
	{
		hsl[0] = -1;
	}
	else if(max == rgbNorm[2] && rgbNorm[1] >= rgbNorm[0])
		hsl[0] = 60.0f * (rgbNorm[1] - rgbNorm[0]) / delta;
	else if(max == rgbNorm[2] && rgbNorm[1] < rgbNorm[0])
		hsl[0] = 60.0f * (rgbNorm[1] - rgbNorm[0]) / delta + 360.0f;
	else if(max == rgbNorm[1])
		hsl[0] = 60.0f * (rgbNorm[0] - rgbNorm[2]) / delta + 120.0f;
	else if(max == rgbNorm[0]) 
		hsl[0] = 60.0f * (rgbNorm[2] - rgbNorm[1]) / delta + 240.0f;
	//l
	hsl[2] = (max + min) / 2.0f;
	//s
	
	if(hsl[2] == 0.0f || delta == 0.0f)
		hsl[1] = 0.0f;
	else if(hsl[2] > 0.0f && hsl[2] <= 0.5f)
		hsl[1] = delta / ( 2.0f * hsl[2]);
	else if(hsl[2] > 0.5f && hsl[2] < 1.0f)
		hsl[1] = delta / (2.0f - 2.0f * hsl[2]);
}

void HslToRgb(Vec3f &rgb, const Vec3f &hsl)
{
	float q, p, hk;
	Vec3f t;

	if(hsl[2] < 0.5f)
		q = hsl[2] * (1.0f + hsl[1]);
	else
		q = hsl[2] + hsl[1] - hsl[2] * hsl[1];

	p = 2.0f * hsl[2] - q;

	hk = hsl[0] / 360.0f;

	t[2] = hk + 1.0f / 3.0f;
	t[1] = hk;
	t[0] = hk - 1.0f / 3.0f;

	for(int i = 0; i < 3; i++)
	{
		if(t[i] < 0.0f)
			t[i] += 1.0f;
		else if(t[i] > 1.0f)
			t[i] -= 1.0f;
	}

	for(int i = 0; i < 3; i++)
	{
		if(t[i] < 1.0f/6.0f)
			rgb[i] = p + (q - p) * 6.0f * t[i];
		else if(t[i] >= 1.0f / 6.0f && t[i] < 0.5f)
			rgb[i] = q;
		else if(t[i] >= 1.0f / 6.0f && t[i] < 2.0f / 3.0f)
			rgb[i] = p + (q - p) * (2.0 / 3.0 - t[i]) * 6.0;
		else
			rgb[i] = p;
	}

	for(int i = 0; i < 3; i++)
		rgb[i] *= 255.0f;
}

int boost_color(cv::InputArray _src, float intensity, cv::OutputArray _dst)
{
	Mat src = _src.getMat();
	
	_dst.create(src.size(), src.type());
	Mat dst = _dst.getMat();
	int height = dst.rows;
	int width = dst.cols;
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			Vec3f rgb = src.at<Vec3f>(i,j);
			Vec3f hsl;
			RgbToHsl(rgb, hsl);
			hsl[1] += intensity;
			if(hsl[1] >= 1.0f)
				hsl[1] = 1.0f;
			HslToRgb(rgb, hsl);
			dst.at<Vec3f>(i,j) = rgb;
		}
	}
    return 0;
}