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
    Mat image, warmifyImg;

    if (argc != 2)
    {
        cout << helper << endl;
        return 1;
    }

    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

    if (!image.data)
    {
        cout << "Error. Image wasn't found." << endl;
        return 2;
    }

    int codeError = warmify(image, warmifyImg, 30);
    if (codeError == 1)
    {
        cout << "Incorrect image type or size of rectangle." << endl;
        return 2;
    }

    namedWindow(srcImgWinName);
    namedWindow(dstImgWinName);
    imshow(srcImgWinName, image);
    imshow(dstImgWinName, warmifyImg);
    waitKey();
    destroyAllWindows();
    return 0;
}
