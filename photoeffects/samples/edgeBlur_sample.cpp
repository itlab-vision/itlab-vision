#include "photoeffects.hpp"
#include <stdio.h>

using namespace cv;

Mat img, filterImg;
int indentTop = 0, indentLeft = 0;

void trackbarIndTop(int pos, void*)
{
	edgeBlur(img, filterImg, indentTop, indentLeft);
	imshow("Edge blur", filterImg);
}

void trackbarIndLeft(int pos, void*)
{
	edgeBlur(img, filterImg, indentTop, indentLeft);
	imshow("Edge blur", filterImg);
}

int main(int argc, char* argv[])
{
	char* filename;

    if (argc == 2)
    {
        filename = argv[1];
    }
    else
    {
        printf("Couldn't open image\n");
        return 0;
    }
    img = imread(filename);

    namedWindow("Edge blur");
    createTrackbar("Indent top", "Edge blur", &indentTop, (int)(img.rows / 2.0f) - 20, trackbarIndTop);
    createTrackbar("Indent left", "Edge blur", &indentLeft, (int)(img.cols / 2.0f) - 20, trackbarIndLeft);

    namedWindow("Image");

    imshow("Image", img);
    imshow("Edge blur", img);

    waitKey();
    return 0;
}
