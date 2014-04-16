#include "photoeffects.hpp"
#include <iostream>

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
    if (argc < 3)
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
    namedWindow(ORIGINAL_IMAGE, CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE, src);
    Mat dst;
    RNG &rng=theRNG()(0);
    filmGrain(src, dst, atoi(argv[2]));
    imshow(FILM_GRAIN_IMAGE, dst);
    cout << "Press any key to EXIT"<<endl;
    waitKey(0);
    imwrite("result.png",dst);
    return 0;
}
