#include "photoeffects.hpp"
#include <stdio.h>

using namespace cv;

int main(int argc, char* argv[])
{
const char *helper =
"./tint_sample <img>\n\
\t<img> - file name contained the processed image\n\
";

Vec3b ColorTint;
Mat BaseColor, img, filterImg;
int valueHue = 0;
int valueDen = 50;

void preparePicture()
{
    BaseColor.create(20, 360, CV_8UC3);
    Vec3b hsv;
    for (int j = 0; j < 360; j++)
    {
        hsv[0] = (j + 1) / 2;
        hsv[1] = 255;
        hsv[2] = 255;
        for (int i = 0; i < 20; i++)
        {
            BaseColor.at<Vec3b>(i,j) = hsv;
        }
    }
    cvtColor(BaseColor, BaseColor, CV_HSV2BGR);
}

void trackbarTint(int pos, void*)
{
    Mat Color;
    BaseColor.copyTo(Color);
    Rect r(pos - 1, 0, 4, 20);
    rectangle(Color, r, Scalar(0));
    imshow("Tint", Color);
    ColorTint = BaseColor.at<Vec3b>(0, pos);

    float den = (float)valueDen / 100.0;
    tint(img, filterImg, ColorTint, den);
    imshow("Filter", filterImg);
}

void trackbarDen(int pos, void *)
{
    float den = (float)valueDen / 100.0;
    tint(img, filterImg, ColorTint, den);
    imshow("Filter", filterImg);
}

int main(int argc, char* argv[])
{
    char* filename;

    if (argc >= 2)
    {
        filename = argv[1];
    }
    else
    {
        printf("Couldn't open image\n");
        printf("%s\n", helper);
        return 1;
    }

    img = imread(filename);

    namedWindow("Tint");
    createTrackbar("Hue", "Tint", &valueHue, 360, trackbarTint);
    createTrackbar("Density(%)", "Tint", &valueDen, 100, trackbarDen);
    preparePicture();

    namedWindow("Image");
    namedWindow("Filter");

    imshow("Tint", BaseColor);
    imshow("Image", img);
    imshow("Filter", img);

    waitKey();
    return 0;
}
