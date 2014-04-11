#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);

    /*
    Calculate relative length between center image and it's corner
    by formula: (x^2 / a^2 + y^2 / b^2),
    this length takes like a maximal kernel size of the filter blur,
    then it multiply on 2,
    number 2 is taken to increase the effect of blur.
    */
    int kSizeOnEdges = (int)(((image.rows / 2.0f)
                            * (image.rows / 2.0f)
                            / (image.rows / 2.0f - indentTop)
                            / (image.rows / 2.0f - indentTop)

                            + (image.cols / 2.0f)
                            * (image.cols / 2.0f)
                            / (image.cols / 2.0f - indentLeft)
                            / (image.cols / 2.0f - indentLeft)) + 0.5f);

    kSizeOnEdges = MAX_KERNELSIZE;

    Mat bearingImage(image.rows + 2 * kSizeOnEdges,
                    image.cols + 2 * kSizeOnEdges,
                    CV_8UC3);
    copyMakeBorder(image, bearingImage, kSizeOnEdges, kSizeOnEdges,
        kSizeOnEdges, kSizeOnEdges, BORDER_REPLICATE);

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
                size = (int)(radius + 0.5f);
                size = size - rand() % 3 + 1;
                if (size == 0)
                {
                    outputImage.at<Vec3b>(i - kSizeOnEdges, j - kSizeOnEdges) =
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
                sumB = (int)(((float)sumB) / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                sumG = (int)(((float)sumG) / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                sumR = (int)(((float)sumR) / ((2.0f * size + 1.0f) * (2.0f * size + 1.0f)) + 0.5f);
                Color = Vec3b(sumB, sumG, sumR);
                outputImage.at<Vec3b>(i - kSizeOnEdges, 
                                    j - kSizeOnEdges) = Color;
            }
        }
    }

    outputImage.convertTo(dst, CV_8UC3);
    return 0;
}
