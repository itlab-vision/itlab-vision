#include "photoeffects.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
using namespace cv;
using namespace std;

const char *ORIGINAL_IMAGE="Original image";
const char *FILM_GRAIN_IMAGE="Faded image";
const char *helper =
"./filmGrain_sample <img>\n\
\t<img> - file name contained the processed image\n\
";

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        cout << helper << endl;
        return 1;
    }
    Mat src=imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(!src.data)
    {
        cout<<"Not found file"<<endl;
        return 1;
    }
    namedWindow(ORIGINAL_IMAGE,CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE,src);
    Mat dst;
    filmGrain(src,dst);
    imshow(FILM_GRAIN_IMAGE,dst);
    cout << "Press any key to EXIT"<<endl;
    waitKey(0);
    return 0;
}
