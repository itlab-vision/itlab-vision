#include "photoeffects.hpp"

using namespace cv;

int vignette(InputArray src, OutputArray dst, Size rect)
{
    CV_Assert(src.type() == CV_8UC3 && rect.height != 0 && rect.width != 0);

    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);
    Mat imgDst(imgSrc.size(), CV_8UC3);
    Vec3b intensity, intensityNew;

    float centerRow = imgSrc.rows / 2.0f;
    float centerCol = imgSrc.cols / 2.0f;
    float aSquare = rect.height * rect.height / 4.0f;
    float bSquare = rect.width * rect.width / 4.0f;
    float ab = rect.height * rect.width / 4.0f;
    float radiusMax = sqrtf(centerRow * centerRow + centerCol * centerCol);

    for (int i = 0; i < imgSrc.rows; i++)
    {
        float iMinusCenterRow = (i - centerRow);
        float iMinusCenterRowSquare = iMinusCenterRow * iMinusCenterRow;
        for (int j = 0; j < imgSrc.cols; j++)
        {
            intensity = imgSrc.at<Vec3b>(i, j);

            float jMinusCenterColSquare = (j - centerCol) * (j - centerCol);
            intensityNew = intensity;
            if (iMinusCenterRowSquare / aSquare + jMinusCenterColSquare / bSquare > 1.0f)
            {
                float dist = sqrtf(iMinusCenterRowSquare + jMinusCenterColSquare);
                float sinFi = iMinusCenterRow / dist;
                float sinFiSquare = sinFi * sinFi;
                float radiusEllipse = ab / sqrtf(aSquare * (1.0f - sinFiSquare) +
                                          bSquare * sinFiSquare);
                float coefficient = 1.0f - ((dist - radiusEllipse) /
                                      (radiusMax - radiusEllipse));

                intensityNew *= coefficient;
            }
            imgDst.at<Vec3b>(i, j) = intensityNew;
        }
    }
    imgDst.copyTo(dst);
    return 0;
}
