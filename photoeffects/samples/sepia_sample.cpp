#include "photoeffects.hpp"
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;

const char *helper = 
"sepia_sample.exe <img> [<hue> <saturation> <value>]\n\
\t<img> - file name contained the processed image\n\
\t<hue> - hue value in the range from 0 to 179\n\
\t<saturation> - saturation value in the range from 0 to 255\n\
\t<value> - shift to increase/decrease the brightness,\n\
\t          changes in the range from 0 to 255\n\
";

int processArguments(int argc, char **argv, 
	Mat &img, Scalar &hue, Scalar &saturation, Scalar &value);

int main(int argc, char **argv)
{
    const char *srcImgWinName = "Initial image", *dstImgWinName = "Processed image";
    Mat img, sepiaImg;
    Scalar hue = Scalar(18), saturation = Scalar(78), value = Scalar(20);
    if (processArguments(argc, argv, img, hue, saturation, value) != 0)
    {
	cout << helper << endl;
	return 1;
    }
    int opRes = sepia(img, sepiaImg, hue, saturation);
    if (opRes != 0)
    {
	cout << "Applying sepia effect failed." << endl;
	return 2;
    }

    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);
    imshow(srcImgWinName, img);
    imshow(dstImgWinName, sepiaImg);
    waitKey();
    destroyAllWindows();
    return 0;
}

int processArguments(int argc, char **argv, 
	Mat &img, Scalar &hue, Scalar &saturation, Scalar &value)
{
    if (argc < 2)
    {
	return 1;
    }
    img = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if (argc > 2)
    {
	hue = Scalar(atoi(argv[2]));
    }
    if (argc > 3)
    {
	saturation = Scalar(atoi(argv[3]));
    }
    if (argc > 4)
    {
	value = Scalar(atoi(argv[4]));
    }
    return 0;
}
