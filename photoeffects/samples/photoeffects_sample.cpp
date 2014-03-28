#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     Point* p=(Point*)userdata;
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
          p->x=x;
          p->y=y;
     }
}

int main(int argc, char** argv)
{
    cout<< "Fade color function test:"<<endl;
    cout<<"    Input name of image:";
    string name;
    cin>>name;
    Mat src=imread(name, CV_LOAD_IMAGE_GRAYSCALE);
    Mat dst(src.rows,src.cols,CV_8UC1);
    Mat srcCopy;
    src.copyTo(srcCopy);
    namedWindow("original",CV_WINDOW_AUTOSIZE);
    Point tmpPoint,startPoint,endPoint;
    setMouseCallback("original", CallBackFunc,&tmpPoint);
    imshow("original",srcCopy);
    cvWaitKey(0);
    startPoint=tmpPoint;
    circle(srcCopy,startPoint,5,CV_RGB(255,255,255),4);
    imshow("original",srcCopy);
    cvWaitKey(0);
    endPoint=tmpPoint;
    line(srcCopy,startPoint, endPoint, CV_RGB(255,255,255),4,CV_AA);
    imshow("original",srcCopy);
    cvWaitKey(0);
    fadeColor(src,dst,startPoint,endPoint);
    namedWindow("Fade image",CV_WINDOW_AUTOSIZE);
    imshow("Fade image",dst);
    imwrite( "Fade_Image.jpg", dst );
    cvWaitKey(0);
    return 0;
}
