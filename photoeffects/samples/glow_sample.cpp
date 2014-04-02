#include "photoeffects.hpp"
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

const char *helper = 
"glow_sample <img> <radius> <intensity>\n\
\t<img> - file name contained the processed image\n\
\t<radius> - radius for Gaussian blur\n\
\t<intensity> - intensity of glow filter\n\
";

int processArguments(int argc, char **argv, Mat &img, float &radius, float &intensity);

int main(int argc, char **argv)
{
    const char *srcImgWinName = "Initial image", *dstImgWinName = "Processed image";
    Mat img, dstImg;
    float radius, intensity;
    if (processArguments(argc, argv, img, radius, intensity) != 0)
    {
        cout << helper << endl;
        return 1;
    }

    int opRes = glow(img, dstImg, radius, intensity);
    switch (opRes)
    {
        case 1:
            cout << "Incorrect image type." << endl;
            return 2;
        case 2:
            cout << "Incorrect value of radius." << endl;
            return 2;
        case 3:
            cout << "Incorrect value of intensity." << endl;
            return 2;
    }
    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);
    imshow(srcImgWinName, img);
    imshow(dstImgWinName, dstImg);
    waitKey();
    destroyAllWindows();
    return 0;
}

int processArguments(int argc, char **argv, Mat &img, float &radius, float &intensity)
{
    if (argc < 4)
    {
        return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    radius = atof(argv[2]);
    intensity = atof(argv[3]);
    return 0;
}