#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;

const string ORIGINAL_IMAGE = "Original image";
const string ANTIQUE_IMAGE = "Antique image";

int main(int argc, char** argv)
{
    Mat src = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(!src.data)
    {
        cout<<"Image file not found!"<<endl;
        return 1;
    }
    Mat texture = imread(argv[2], CV_LOAD_IMAGE_COLOR);
    if(!texture.data)
    {
        cout<<"Texture file not found!"<<endl;
        return 2;
    }
    Mat srcCopy;
    src.copyTo(srcCopy);
    Mat dst(src.rows, src.cols, CV_8UC3);
    namedWindow(ORIGINAL_IMAGE, CV_WINDOW_AUTOSIZE);
    imshow(ORIGINAL_IMAGE,srcCopy);
    antique(src, texute, dst);
    namedWindow(ANTIQUE_IMAGE,dst);
    cout<<"Press any key"<<endl;
    waitKey(0);
    imwrite(argv[3],dst);
    destroyAllWindows();
    return 0;
}
