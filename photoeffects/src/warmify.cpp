#include "photoeffects.hpp"

using namespace cv;

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);
    dst.create(src.size(), CV_8UC3);
    Mat imgDst = dst.getMat();
    Vec3b intensity, intensityNew;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);
            intensityNew[0] = intensity[0];
            uchar g = (intensity[1] + delta) >> 8;
            uchar r = (intensity[2] + delta) >> 8;
            intensityNew[1] = g * 255 + (1 - g) * intensity[1] + (1 - g) * delta;
            intensityNew[2] = r * 255 + (1 - r) * intensity[2] + (1 - r) * delta;
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    return 0;
}

