#include "photoeffects.hpp"

using namespace cv;

int tint(InputArray src, OutputArray dst, 
        const Vec3b &colorTint, float density)
{
    CV_Assert(src.type() == CV_8UC3);
    CV_Assert(density >= 0.0f || density <= 1.0f);
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            Vec3b colorDest = image.at<Vec3b>(i, j);
            colorDest = colorTint * density + (1 - density) * colorDest;
            outputImage.at<Vec3b>(i, j) = colorDest;
        }
    }
    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
