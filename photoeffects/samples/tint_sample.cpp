#include "photoeffects.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;

Vec3b ColorTint;
Mat BaseColor, Color;
int valueHue = 0;
int valueDen = 50;

void trackbarTint(int pos, void*)
{
    BaseColor.copyTo(Color);
    valueHue = pos;
    Rect r;
    r.x = pos-1;
    r.y = 0;
    r.width = 4;
    r.height = 20;
    rectangle(Color, r, Scalar(0));
    imshow("Tint", Color);
    ColorTint = BaseColor.at<Vec3b>(0, pos);
}

void trackbarDensity(int pos, void*)
{
    valueDen = pos;
}

int main(int argc, char* argv[])
{
	char* filename;
    Mat img, filterImg;

	if (argc >= 2)
	{
		filename = argv[1];
	}
	else
	{
		printf("Couldn't open image\n");
        waitKey();
		return 0;
	}
    BaseColor = imread("/home/dmitry/Images/hue.jpg", 1);
    img = imread(filename);

	namedWindow("Tint");
    createTrackbar("Hue", "Tint", &valueHue, 360, trackbarTint);
    createTrackbar("Density(%)", "Tint", &valueDen, 100, trackbarDensity);

	namedWindow("Image");
    namedWindow("Filter");

    imshow("Tint", BaseColor);
	imshow("Image", img);
    imshow("Filter", img);

    char c;
    while(1)
    {
        c = waitKey();
        if (c == 27)
        {
            return 0;
        }
        else if (c == ' ')
        {
            float den = (float)valueDen / 100.0;
            img.copyTo(filterImg);
            tint(img, ColorTint, den, filterImg);
            imshow("Filter", filterImg);
        }
    }
	return 0;
}
