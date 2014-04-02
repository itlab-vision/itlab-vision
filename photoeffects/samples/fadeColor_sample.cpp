#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;

const string ORIGINAL_IMAGE="Original image";
const string FADED_IMAGE="Faded image";

Point startPoint,endPoint;
int numberChoosenPoint=0;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
    Mat src=*((Mat*)userdata);
    Mat srcCopy;
    src.copyTo(srcCopy);
    if  ( event == EVENT_LBUTTONDOWN )
    {
        switch(numberChoosenPoint)
        {
        case 0:
            startPoint=Point(x,y);
            numberChoosenPoint++;
            circle(srcCopy,Point(x,y),5,CV_RGB(255,50,255),4);
            imshow(ORIGINAL_IMAGE,srcCopy);
            break;
        case 1:
            endPoint=Point(x,y);
            numberChoosenPoint++;
            Mat dst;
            fadeColor(src,dst,startPoint,endPoint);
            namedWindow(FADED_IMAGE,CV_WINDOW_AUTOSIZE);
            imshow(FADED_IMAGE,dst);
            break;
        }
    }
}

int main(int argc, char** argv)
{
    Mat src=imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(!src.data)
    {
        cout<<"Not found file"<<endl;
        return 0;
    }
    namedWindow(ORIGINAL_IMAGE,CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE,src);
    setMouseCallback(ORIGINAL_IMAGE, CallBackFunc,&src);
    cout << "Choose two picture on image"<<endl;
    cout << "Press any key to EXIT"<<endl;
    waitKey(0);
    destroyAllWindows();
    return 0;
}
