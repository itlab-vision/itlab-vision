#include "photoeffects.hpp"

using namespace cv;

/*
// Function for applying a vignette effect to iamge
//
// API
// int vignette(InputArray src, OutputArray dst, Size rect);
// INPUT
// src - source image
// rect - rectangle describe an ellipse,
// which is outside the dark effect is applied
// OUTPUT
// dst - the image with vignette effect
// RESULT
// Error status
*/

int vignette(InputArray src, OutputArray dst, Size rect)
{
    CV_Assert(src.type() == CV_8UC3 && rect.height != 0 && rect.width != 0);
    Mat imgSrc(src.size(), CV_8UC3);
    imgSrc = src.getMat();
    Mat imgDst(imgSrc.size(), CV_8UC3);
    Vec3b intensity, intensityNew;

    int centerRow = imgSrc.rows / 2;
    int centerCol = imgSrc.cols / 2;
    float aSquare = (rect.height / 2.0f) * (rect.height / 2.0f);
    float bSquare = (rect.width / 2.0f) * (rect.width / 2.0f);
    float ab = (rect.height / 2.0f) * (rect.width / 2.0f);
    float radiusEllipse = 0.0f;
    float radiusMax = sqrt((imgSrc.rows / 2) * (imgSrc.rows / 2) +
                           (imgSrc.cols / 2) * (imgSrc.cols / 2));
    float dist = 0.0f;
    float sinFi = 0.0f;
    float coefficient = 0.0f;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);

            intensityNew = intensity;
            if ((i - centerRow) * (i - centerRow) / aSquare +
                    (j - centerCol) * (j - centerCol) / bSquare > 1)
            {
                dist = sqrtf((i - centerRow) * (i - centerRow) +
                             (j - centerCol) * (j - centerCol));
                sinFi = (i - centerRow) / dist;
                radiusEllipse = ab / sqrt(aSquare * (1 - sinFi * sinFi) +
                                          bSquare * sinFi * sinFi);
                coefficient = 1.0f - ((dist - radiusEllipse) /
                                      (radiusMax - radiusEllipse));

                intensityNew.val[0] = (uchar)(intensity.val[0] * coefficient);
                intensityNew.val[1] = (uchar)(intensity.val[1] * coefficient);
                intensityNew.val[2] = (uchar)(intensity.val[2] * coefficient);
            }
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    imgDst.convertTo(dst, CV_8UC3);
    return 0;
}
