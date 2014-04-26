#include "photoeffects.hpp"

using namespace cv;

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    CV_Assert(src.type() == CV_8UC3);

    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);
    dst.create(imgSrc.size(), CV_8UC3);
    Mat imgDst = dst.getMat();
    Vec3b intensityNew;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensityNew = imgSrc.at<Vec3b>(i, j);
            intensityNew[1] = (intensityNew[1] + delta < 255) ? (uchar)(intensityNew[1] + delta) : 255;
            intensityNew[2] = (intensityNew[2] + delta < 255) ? (uchar)(intensityNew[2] + delta) : 255;
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    return 0;
}

