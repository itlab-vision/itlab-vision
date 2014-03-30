#include "photoeffects.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <iostream>

using namespace cv;

int main(int argc, char** argv)
{
    Mat image;
    Mat dst;
    image = imread(argv[1], 1);

    Mat data(image);
    image.convertTo(data, CV_32F);

    float intensity = atof(argv[3]);
    
    boost_color(data, intensity, dst);

    imwrite(argv[2], dst);

    return 0;
}