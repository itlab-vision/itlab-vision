#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15

void prepareForFilter(Mat& input, Mat& outputImage, int size)
{
    for (int i = 0; i < outputImage.rows; i++)
    {
        for (int j = 0; j < outputImage.cols; j++)
        {
            outputImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
        }
    }
    for (int i = 0; i < input.rows; i++)
    {
        for (int j = 0; j < input.cols; j++)
        {
            outputImage.at<Vec3b>(i + size, j + size) = input.at<Vec3b>(i, j);
        }
    }
}

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);

    int kSizeOnEdges = (int)(((image.rows / 2.0f)
                            * (image.rows / 2.0f)
                            / (image.rows / 2.0f - indentTop)
                            / (image.rows / 2.0f - indentTop)

                            + (image.cols / 2.0f)
                            * (image.cols / 2.0f)
                            / (image.cols / 2.0f - indentLeft)
                            / (image.cols / 2.0f - indentLeft)) * 2.0f + 0.5f);
    if (kSizeOnEdges > MAX_KERNELSIZE)
    {
        kSizeOnEdges = MAX_KERNELSIZE;
    }

    Mat bearingImage(image.rows + 2 * kSizeOnEdges,
                    image.cols + 2 * kSizeOnEdges,
                    CV_8UC3);
    prepareForFilter(image, bearingImage, kSizeOnEdges);

    float radius;
    int size;
    int sumB, sumG, sumR;
    Vec3b Color;
    for (int i = kSizeOnEdges; i < (bearingImage.rows - kSizeOnEdges); i++)
    {
        for (int j = kSizeOnEdges; j < (bearingImage.cols - kSizeOnEdges); j++)
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
                outputImage.at<Vec3b>(i - kSizeOnEdges, j - kSizeOnEdges) =
                    bearingImage.at<Vec3b>(i, j);
                continue;
            }
            else
            {
                sumB = sumG = sumR = 0;
                size = (int)(2.0f * radius + 0.5f);
                if (size > MAX_KERNELSIZE)
                {
                    size = MAX_KERNELSIZE;
                }
                for (int x = i - size; x < i + size; x++)
                {
                    for (int y = j - size; y < j + size; y++)
                    {
                        Color = bearingImage.at<Vec3b>(x, y);
                        sumB = sumB + Color[0];
                        sumG = sumG + Color[1];
                        sumR = sumR + Color[2];
                    }
                }
                sumB = (int)((float)sumB / (4.0f * size * size) + 0.5f);
                sumG = (int)((float)sumG / (4.0f * size * size) + 0.5f);
                sumR = (int)((float)sumR / (4.0f * size * size) + 0.5f);
                Color = Vec3b(sumB, sumG, sumR);
                outputImage.at<Vec3b>(i - kSizeOnEdges, j - kSizeOnEdges) = Color;
            }
        }
    }

    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
