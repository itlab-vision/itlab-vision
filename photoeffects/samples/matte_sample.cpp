#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;

const string ORIGINAL_IMAGE = "Original image";
const string MATTE_IMAGE = "Matte image";

Point firstPoint, secondPoint;
int numberOfChoosenPoints = 0;
float sigma = 0.0f;
const char *helper = "matte_sample.exe <img> <sigma>\n\
\t<img>-file name contained the processed image\n\
\t<sigma>-float param - power of the blur";

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Mat src=*((Mat*)userdata);
    if (event == EVENT_LBUTTONDOWN)
    {
        switch(numberOfChoosenPoints)
        {
            case 0:
            {
                firstPoint = Point(x,y);
                numberOfChoosenPoints++;
                break;
            }
            case 1:
            {
                secondPoint = Point(x,y);
                numberOfChoosenPoints++;
                Mat dst;
                matte(src, dst, firstPoint, secondPoint, sigma);
                namedWindow(MATTE_IMAGE, CV_WINDOW_AUTOSIZE);
                imshow(MATTE_IMAGE, dst);
                break;
            }
        }
    }
}
int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout << helper << endl;
        return 1;
    }
    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(src.empty())
    {
        cout<<"Image file not found!"<<endl;
        return 1;
    }
    sigma=atof(argv[2]);
    namedWindow(ORIGINAL_IMAGE, CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE, src);
    setMouseCallback(ORIGINAL_IMAGE,CallBackFunc, &src);
    cout<<"Press any key"<<endl;
    waitKey(0);
    destroyAllWindows();
    return 0;
}