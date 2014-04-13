#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15
#define PI 3.14159265359

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    CV_Assert(src.type() == CV_8UC3);
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);
    float kSizeEdges = (image.rows / 2.0f)
                    * (image.rows / 2.0f)
                    / (image.rows / 2.0f - indentTop)
                    / (image.rows / 2.0f - indentTop)

                    + (image.cols / 2.0f)
                    * (image.cols / 2.0f)
                    / (image.cols / 2.0f - indentLeft)
                    / (image.cols / 2.0f - indentLeft);
    if (kSizeEdges > MAX_KERNELSIZE)
    {
        kSizeEdges = MAX_KERNELSIZE;
    }
    Mat bearingImage(image.rows + 2 * kSizeEdges,
                    image.cols + 2 * kSizeEdges,
                    CV_8UC3);
    copyMakeBorder(image, bearingImage, kSizeEdges, kSizeEdges,
        kSizeEdges, kSizeEdges, BORDER_REPLICATE);

    float radius;
    int size;
    float B, G, R, sumC;
    Vec3b Color;
    float coeff;
    for (int i = kSizeEdges; i < (bearingImage.rows - kSizeEdges); i++)
    {
        for (int j = kSizeEdges; j < (bearingImage.cols - kSizeEdges); j++)
        {
            radius = (bearingImage.rows / 2.0f - i)
                    * (bearingImage.rows / 2.0f - i)
                    / (image.rows / 2.0f - indentTop)
                    / (image.rows / 2.0f - indentTop)

                    + (bearingImage.cols / 2.0f - j)
                    * (bearingImage.cols / 2.0f - j)
                    / (image.cols / 2.0f - indentLeft)
                    / (image.cols / 2.0f - indentLeft);
            if (radius < 1.0f)
            {
                outputImage.at<Vec3b>(i - kSizeEdges, j - kSizeEdges) =
                    bearingImage.at<Vec3b>(i, j);
                continue;
            }
            else
            {
                R = G = B = sumC = 0.0f;
                size = radius;
                radius -= 0.5f;
                radius *= radius;
                if (size > kSizeEdges)
                {
                    size = kSizeEdges;
                }
                for (int x = i - size; x <= i + size; x++)
                {
                    for (int y = j - size; y <= j + size; y++)
                    {
                        coeff = 1.0f / (2.0f * PI * radius)
                                * exp(- ((x - i)*(x - i) + (y - j)*(y - j))
                                      / (2.0f * radius));

                        Color = bearingImage.at<Vec3b>(x, y);
                        B = B + coeff * Color[0];
                        G = G + coeff * Color[1];
                        R = R + coeff * Color[2];
                        sumC += coeff;
                    }
                }
                B /= sumC;
                G /= sumC;
                R /= sumC;
                Color = Vec3b(B, G, R);
                outputImage.at<Vec3b>(i - kSizeEdges, j - kSizeEdges) = Color;
            }
        }
    }

    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
