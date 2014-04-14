#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);
    
    CV_Assert(indentTop >= 0 && indentTop <= (image.rows / 2 - 10));
    CV_Assert(indentLeft >= 0 && indentLeft <= (image.cols / 2 - 10));

    float halfWidth = (image.cols / 2.0f) * (image.cols / 2.0f);
    float halfHeight = (image.rows / 2.0f) * (image.rows / 2.0f);
    float a = (image.cols / 2.0f - indentLeft) 
            * (image.cols / 2.0f - indentLeft);
    float b = (image.rows / 2.0f - indentTop) 
            * (image.rows / 2.0f - indentTop);
    int kSizeEdges = halfWidth / a + halfHeight / b;

    if (kSizeEdges > MAX_KERNELSIZE)
    {
        kSizeEdges = MAX_KERNELSIZE;
    }
    Mat bearingImage(image.rows + 2 * kSizeEdges,
                    image.cols + 2 * kSizeEdges,
                    CV_8UC3);
    copyMakeBorder(image, bearingImage, kSizeEdges, kSizeEdges,
        kSizeEdges, kSizeEdges, BORDER_REPLICATE);

    int size, maxI = bearingImage.rows - kSizeEdges,
    maxJ = bearingImage.cols - kSizeEdges;
    Vec3f sumF;
    Vec3b Color;
    float radius, sumC, coeff;
    float bearHalfWidth = bearingImage.cols / 2.0f;
    float bearHalfHeight = bearingImage.rows / 2.0f;

    for (int i = kSizeEdges; i < maxI; i++)
    {
        for (int j = kSizeEdges; j < maxJ; j++)
        {
            radius = (bearHalfHeight - i)
                    * (bearHalfHeight - i)
                    / b

                    + (bearHalfWidth - j)
                    * (bearHalfWidth - j)
                    / a;
            if (radius < 1.0f)
            {
                outputImage.at<Vec3b>(i - kSizeEdges, j - kSizeEdges) =
                    bearingImage.at<Vec3b>(i, j);
                continue;
            }
            sumF[0] = 0.0f;
            sumF[1] = 0.0f;
            sumF[2] = 0.0f;
            sumC = 0.0f;
            size = radius;
            radius -= 0.5f;
            radius *= 2.0f * radius;
            if (size > kSizeEdges)
            {
                size = kSizeEdges;
            }
            for (int x = -size; x <= size; x++)
            {
                for (int y = -size; y <= size; y++)
                {
                    coeff = 1.0f / (CV_PI * radius)
                            * exp(- (x * x + y * y) / radius);

                    Color = bearingImage.at<Vec3b>(x + i, y + j);
                    sumF = sumF + (Vec3f) (coeff * Color);
                    sumC += coeff;
                }
            }
            sumF = sumF * (1.0f / sumC);
            outputImage.at<Vec3b>(i - kSizeEdges, j - kSizeEdges) = sumF;
        }
    }

    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
