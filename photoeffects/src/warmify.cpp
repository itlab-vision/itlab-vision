#include "photoeffects.hpp"

using namespace cv;

/*
// Function for applying warmify filter to image
//
// API
// int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta);
// INPUT
// src- source image
// delta - value, increase a warm components of colors which on
// OUTPUT
// dst - the image with warmify filter effect
// RESULT
// Error status
*/

int warmify(cv::InputArray src, cv::OutputArray dst, uchar delta)
{
    CV_Assert(src.type() == CV_8UC3);

    Mat imgSrc(src.size(), CV_8UC3);
    imgSrc = src.getMat();
    Mat imgDst(imgSrc.size(), CV_8UC3);

    Vec3b intensity, intensityNew;
    int r = 0;
    int g = 0;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);
            intensityNew.val[0] = intensity.val[0];
            g = intensity.val[1] + delta;
            if (g > 255) g = 255;
            r = intensity.val[2] + delta;
            if (r > 255) r = 255;
            intensityNew.val[1] = (uchar)g;
            intensityNew.val[2] = (uchar)r;
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    imgDst.convertTo(dst, CV_8UC3);
    return 0;
}

