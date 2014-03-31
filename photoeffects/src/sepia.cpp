#include "photoeffects.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

int sepia(InputArray src, OutputArray dst, Scalar hue, Scalar saturation, 
	Scalar value)
{
    Mat img = src.getMat(), hsvImg, sepiaH, sepiaS;

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