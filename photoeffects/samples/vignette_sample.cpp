#include "photoeffects.hpp"
#include <iostream>

using namespace cv;
using namespace std;

const char *helper =
"./sepia_sample <img>\n\
\t<img> - file name contained the processed image\n\
";

int main(int argc, char** argv)
{
    const char *srcImgWinName = "Initial image",
               *dstImgWinName = "Processed image";
    Mat image, vignetteImg;
    Size rectangle;

    if (argc < 2)
    {
        cout << helper << endl;
        return 1;
    }

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    rectangle.height = image.rows / 1.5f;
    rectangle.width = image.cols / 2.0f;

    if (image.data == NULL)
    {
        cout << "Error. Image wasn't found." << endl;
        return 2;
    }

    int codeError = vignette(image, vignetteImg, rectangle);
    if (codeError == 1)
    {
        cout << "Incorrect image type or size of rectangle." << endl;
        return 2;
    }

    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);
    imshow(srcImgWinName, image);
    imshow(dstImgWinName, vignetteImg);
    waitKey();
    destroyAllWindows();
	return 0;
}
