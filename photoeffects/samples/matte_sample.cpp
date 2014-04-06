#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;

const string ORIGINAL_IMAGE = "Original image";
const string MATTE_IMAGE = "Matte image";

Point topleftPoint, bottomrightPoint;
int numberOfChoosenPoints = 0;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Mat src=*((Mat*)userdata);
    Mat srcCopy;
    src.copyTo(srcCopy);
    if (event == EVENT_LBUTTONDOWN)
    {
        switch(numberOfChoosenPoints)
        {
            case 0:
            {
                topleftPoint = Point(x,y);
                numberOfChoosenPoints++;
                break;
            }
            case 1:
            {
                bottomrightPoint = Point(x,y);
                numberOfChoosenPoints++;
                Mat dst(src.rows, src.cols, CV_32FC3);
                matte(srcCopy, topleftPoint, bottomrightPoint, dst);
                namedWindow(MATTE_IMAGE, CV_WINDOW_AUTOSIZE);
                imshow(MATTE_IMAGE, dst);
                imwrite("output.jpg",dst);
                break;
            }
        }
    }
}
int main(int argc, char** argv)
{
    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(!src.data)
    {
        cout<<"Image file not found!"<<endl;
        return 1;
    }
    
    namedWindow(ORIGINAL_IMAGE, CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE, src);
    setMouseCallback(ORIGINAL_IMAGE,CallBackFunc, &src);
    
    cout<<"Press any key"<<endl;
    waitKey(0);
    
    destroyAllWindows();
    return 0;
}