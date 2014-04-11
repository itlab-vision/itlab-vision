#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);

    Mat bearingImage(image.rows + 2 * MAX_KERNELSIZE,
                    image.cols + 2 * MAX_KERNELSIZE,
                    CV_8UC3);
    copyMakeBorder(image, bearingImage, MAX_KERNELSIZE, MAX_KERNELSIZE,
        MAX_KERNELSIZE, MAX_KERNELSIZE, BORDER_REPLICATE);

    float radius;
    int size;
    int sumB, sumG, sumR;
    Vec3b Color;
    for (int i = MAX_KERNELSIZE; i < (bearingImage.rows - MAX_KERNELSIZE); i++)
    {
        for (int j = MAX_KERNELSIZE; j < (bearingImage.cols - MAX_KERNELSIZE); j++)
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
                outputImage.at<Vec3b>(i - MAX_KERNELSIZE, j - MAX_KERNELSIZE) =
                    bearingImage.at<Vec3b>(i, j);
                continue;
            }
            else
            {
                sumB = sumG = sumR = 0;
                size = (int)(radius + 0.5f) /*- rand() % 2*/;
                if (size == 0)
                {
                    outputImage.at<Vec3b>(i - MAX_KERNELSIZE, j - MAX_KERNELSIZE) =
                        bearingImage.at<Vec3b>(i, j);
                    continue;
                }
                else if (size > MAX_KERNELSIZE)
                {
                    size = MAX_KERNELSIZE;
                }
                for (int x = i - size; x <= i + size; x++)
                {
                    for (int y = j - size; y <= j + size; y++)
                    {
                        Color = bearingImage.at<Vec3b>(x, y);
                        sumB = sumB + Color[0];
                        sumG = sumG + Color[1];
                        sumR = sumR + Color[2];
                    }
                }
                sumB = (int)(sumB / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                sumG = (int)(sumG / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                sumR = (int)(sumR / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                Color = Vec3b(sumB, sumG, sumR);
                outputImage.at<Vec3b>(i - MAX_KERNELSIZE, 
                                    j - MAX_KERNELSIZE) = Color;
            }
        }
    }

    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
