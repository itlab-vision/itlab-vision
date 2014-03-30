#include "photoeffects.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
int main(int argc, char** argv)
{
    Mat src=imread(argv[1], CV_LOAD_IMAGE_COLOR),dst;
    namedWindow("ORIGINAL_IMAGE",CV_WINDOW_AUTOSIZE);
    imshow("ORIGINAL_IMAGE",src);
    filmGrain(src,dst);
    imshow("ORIGINAL_IMAGE",dst);
    waitKey(0);
    return 0;
}
