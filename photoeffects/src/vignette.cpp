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

    Mat imgSrc = src.getMat();
    Mat imgDst(imgSrc.size(), CV_8UC3);
    Vec3b intensity, intensityNew;

    float centerRow = imgSrc.rows / 2.0f;
    float centerCol = imgSrc.cols / 2.0f;
    float aSquare = rect.height * rect.height / 4.0f;
    float bSquare = rect.width * rect.width / 4.0f;
    float ab = rect.height * rect.width / 4.0f;
    float radiusEllipse = 0.0f;
    float radiusMax = sqrtf(centerRow * centerRow + centerCol * centerCol);
    float iMinusCenterRow = 0.0f;
    float iMinusCenterRowSquare = 0.0f;
    float jMinusCenterColSquare = 0.0f;
    float dist = 0.0f;
    float sinFi = 0.0f;
    float sinFiSquare = 0.0f;
    float coefficient = 0.0f;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        iMinusCenterRow = (i - centerRow);
        iMinusCenterRowSquare = iMinusCenterRow * iMinusCenterRow;
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);

            jMinusCenterColSquare = (j - centerCol) * (j - centerCol);
            intensityNew = intensity;
            if (iMinusCenterRowSquare / aSquare + jMinusCenterColSquare / bSquare > 1)
            {
                dist = sqrtf(iMinusCenterRowSquare + jMinusCenterColSquare);
                sinFi = iMinusCenterRow / dist;
                sinFiSquare = sinFi * sinFi;
                radiusEllipse = ab / sqrtf(aSquare * (1.0f - sinFiSquare) +
                                          bSquare * sinFiSquare);
                coefficient = 1.0f - ((dist - radiusEllipse) /
                                      (radiusMax - radiusEllipse));

                intensityNew *= coefficient;
            }
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    imgDst.convertTo(dst, CV_8UC3);
    return 0;
}
