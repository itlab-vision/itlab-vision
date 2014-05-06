#include "photoeffects.hpp"
#include <stdlib.h>
#include <iostream>

#include <stdio.h>
#define TIMER_START(name) int64 t_##name = getTickCount()
#define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
            1000.f * ((getTickCount() - t_##name) / getTickFrequency()))

using namespace cv;
using namespace std;

const char *helper = 
"./glow_sample <img> <sigma> <intensity>\n\
\t<img> - file name contained the source image, 3-channel, RGB-image\n\
\t<radius> - Gaussian kernel size, must be positive and odd number\n\
\t<intensity> - intensity of glow filter, must be real number from 0.0 to 1.0 \n\
";

int processArguments(int argc, char **argv, Mat &img, int &radius, float &intensity);

int main(int argc, char **argv)
{
    const char *srcImgWinName = "Initial image", *dstImgWinName = "Processed image";
    Mat img, dstImg;
    float intensity;
	int radius;
    if (processArguments(argc, argv, img, radius, intensity) != 0)
    {
        cout << helper << endl;
        return 1;
    }

    int errorCode = 0;
    try
    {
		TIMER_START(ALL);
        glow(img, dstImg, radius, intensity);
		TIMER_END(ALL);
    }
    catch (cv::Exception &e)
    {
        errorCode = e.code;
    }
    
    if (errorCode == 0)
    {
        namedWindow(srcImgWinName);
        namedWindow(dstImgWinName);
        imshow(srcImgWinName, img);
        imshow(dstImgWinName, dstImg);
        waitKey();
        destroyAllWindows();
    }
    return 0;
}

int processArguments(int argc, char **argv, Mat &img, int &radius, float &intensity)
{
    if (argc < 4)
    {
        return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    radius = atoi(argv[2]);
    intensity = (float)atof(argv[3]);
    
    return 0;
}