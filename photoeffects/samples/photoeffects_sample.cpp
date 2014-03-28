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
    Mat* image=(Mat*)userdata;
    if  ( event == EVENT_LBUTTONDOWN )
    {
        numberChoosenPoint++;
        switch(numberChoosenPoint)
        {
        case 1:
            startPoint=Point(x,y);
            break;
        case 2:
            endPoint=Point(x,y);
            break;
        }
        circle(*image,Point(x,y),5,CV_RGB(255,50,255),4);
        cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
        imshow(ORIGINAL_IMAGE,*image);

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
    Mat dst(src.rows,src.cols,CV_8UC3);
    Mat srcCopy;
    src.copyTo(srcCopy);
    namedWindow(ORIGINAL_IMAGE,CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE,srcCopy);
    setMouseCallback(ORIGINAL_IMAGE, CallBackFunc,&srcCopy);
    do
    {
        cout<<"Choose two point and press any key"<<endl;
        waitKey(0);
    }
    while(numberChoosenPoint!=2);
    fadeColor(src,dst,startPoint,endPoint);
    namedWindow(FADED_IMAGE,CV_WINDOW_AUTOSIZE);
    imshow(FADED_IMAGE,dst);
    cout << "Press any key to EXIT"<<endl;
    waitKey(0);
    imwrite( argv[2], dst );
    destroyAllWindows();
    return 0;
}
