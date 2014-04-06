#include "photoeffects.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Error. Write the name of image as parameter." << endl;
        return -1;
    }
    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if (!image.data)
    {
        cout << "Error. Image wasn't found." << endl;
        return -1;
    }
    namedWindow(argv[1], WINDOW_AUTOSIZE);
    Mat img_dst;
    imshow(argv[1], image);
    if (warmify(image, img_dst, 30) == 0)
    {
        imshow(argv[1], img_dst);
        imwrite("/home/vlad/Изображения/sunset1_warm.jpg", img_dst);
    }
    else
    {
        cout << "Error. Wrong parameters." << endl;
    }
    waitKey(0);
    return 0;
}
