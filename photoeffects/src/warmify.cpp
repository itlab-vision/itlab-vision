#include "photoeffects.hpp"

using namespace cv;

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);
    dst.create(src.size(), CV_8UC3);
    Mat imgDst = dst.getMat();

    Mat warmifyMat(src.size(), CV_8UC3, Scalar(0, delta, delta));

    imgDst = imgSrc + warmifyMat;
    return 0;
}