#include "photoeffects.hpp"
#include <stdlib.h>
#include <iostream>

using namespace cv;
using namespace std;

const char *helper = 
"glow_sample <img> <sigma> <intensity>\n\
\t<img> - file name contained the source image, 3-channel, RGB-image\n\
\t<sigma> - Gaussian kernel standard deviation, must be positive real number\n\
\t<intensity> - intensity of glow filter, must be real number from 0.0 to 1.0 \n\
";

int processArguments(int argc, char **argv, Mat &img, float &sigma, float &intensity);

int main(int argc, char **argv)
{
    const char *srcImgWinName = "Initial image", *dstImgWinName = "Processed image";
    Mat img, dstImg;
    float sigma, intensity;
    if (processArguments(argc, argv, img, sigma, intensity) != 0)
    {
        cout << helper << endl;
        return 1;
    }

    int opRes = glow(img, dstImg, sigma, intensity);
    switch (opRes)
    {
        case 1:
            cout << "Incorrect image type." << endl;
            return 2;
        case 2:
            cout << "Incorrect value of sigma." << endl;
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

int processArguments(int argc, char **argv, Mat &img, float &sigma, float &intensity)
{
    if (argc < 4)
    {
        return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    sigma = atof(argv[2]);
    intensity = atof(argv[3]);
    cout << sigma << " " << intensity << endl;
    return 0;
}