#include "photoeffects.hpp"

using namespace cv;

int tint(Mat image, Vec3b colorTint, float density, Mat& filterImg)
{
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Vec3b colorDest = image.at<Vec3b>(i, j);
            colorDest[0] = (uchar)((colorTint[0] - colorDest[0])*density + colorDest[0]);
            colorDest[1] = (uchar)((colorTint[1] - colorDest[1])*density + colorDest[1]);
            colorDest[2] = (uchar)((colorTint[2] - colorDest[2])*density + colorDest[2]);
            filterImg.at<Vec3b>(i, j) = colorDest;
        }
    }
    return 0;
}
