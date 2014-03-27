#include "photoeffects.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;

int main(int argc, char** argv)
{
    Mat image;
    Mat dst;
    image = imread("image-opacity.jpg", 1);
    imwrite( "img.jpg", image );
    Mat data(image);
    image.convertTo(data, CV_32F);
    glow(data, 9, 0.9, dst);
    return 0;
}