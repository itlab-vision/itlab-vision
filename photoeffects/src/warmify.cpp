#include "photoeffects.hpp"

using namespace cv;

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);
    Mat imgDst(imgSrc.size(), CV_8UC3);
    Vec3b intensity, intensityNew;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);
            intensityNew[0] = intensity[0];
            intensityNew[1] = (intensity[1] + delta < 255) ? (uchar)(intensity[1] + delta) : 255;
            intensityNew[2] = (intensity[2] + delta < 255) ? (uchar)(intensity[2] + delta) : 255;
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    imgDst.copyTo(dst);
    return 0;
}

