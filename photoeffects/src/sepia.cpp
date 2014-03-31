#include "photoeffects.hpp"
#include <vector>

using namespace cv;

int sepia(InputArray src, OutputArray dst, Scalar hue, Scalar saturation, 
	Scalar value)
{
    Mat img = src.getMat(), hsvImg, sepiaH, sepiaS;
    if (src.type() != CV_8UC1)
    {
	return 1;
    }
    if (hue[0] < 0 || hue[1] > 179 ||
	saturation[0] < 0 || saturation[0] > 255)
    {
	return 2;
    }
    vector<Mat> sepiaPlanes;
    sepiaPlanes.resize(3);
    sepiaH.create(img.size(), CV_8UC1);
    sepiaS.create(img.size(), CV_8UC1);
    sepiaH.setTo(hue);
    sepiaS.setTo(saturation);
    sepiaPlanes[0] = sepiaH;
    sepiaPlanes[1] = sepiaS;
    sepiaPlanes[2] = img + value;
    merge(sepiaPlanes, hsvImg);
    
    cvtColor(hsvImg, dst, CV_HSV2BGR);
    return 0;
}