#include "photoeffects.hpp"
#include "stdio.h"

using namespace cv;

int tint(InputArray src, OutputArray dst, 
        const Vec3b &colorTint, float density)
{
    CV_Assert(src.type() == CV_8UC3);
    CV_Assert(density >= 0.0f && density <= 1.0f);
    dst.create(src.size(), CV_8UC3);
    Mat image = src.getMat(), outputImage = dst.getMat();

    float negDen = 1 - density;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Vec3b colorDest = image.at<Vec3b>(i, j);
            colorDest = colorTint * density + negDen * colorDest;
            outputImage.at<Vec3b>(i, j) = colorDest;
        }
    }
    return 0;
}
