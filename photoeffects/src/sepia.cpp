#include "photoeffects.hpp"
#include <vector>

using namespace cv;

int sepia(InputArray src, OutputArray dst)
{
    Mat img = src.getMat(), hsvImg, sepiaH, sepiaS;
    Scalar hue(19), saturation(78), value(20);
    if (src.type() != CV_8UC1)
    {
	return 1;
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