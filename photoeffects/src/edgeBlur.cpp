#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

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

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentRight)
{
    //Mat image = src.getMat(), outputImage(image.size(), CV_8UC3);
    Mat image, outputImage;
    image = imread("/home/dmitry/Images/lena.jpg", CV_LOAD_IMAGE_COLOR);
    outputImage.create(image.size(), CV_8UC3);


    int max_KernelSize = (int)(((image.rows / 2.0f)
                            * (image.rows / 2.0f)
                            / (image.rows / 2.0f - indentTop)
                            / (image.rows / 2.0f - indentTop)

                            + (image.cols / 2.0f)
                            * (image.cols / 2.0f)
                            / (image.cols / 2.0f - indentRight)
                            / (image.cols / 2.0f - indentRight)) * 5.0f + 0.5f);

    Mat bearingImage(image.rows + 2 * max_KernelSize, 
                    image.cols + 2 * max_KernelSize, 
                    CV_8UC3);
    prepareForFilter(image, bearingImage, max_KernelSize);

    float radius;
    int size;
    int sumB, sumG, sumR;
    Vec3b Color;
    for (int i = max_KernelSize; i < (bearingImage.rows - max_KernelSize); i++)
    {
        for (int j = max_KernelSize; j < (bearingImage.cols - max_KernelSize); j++)
        {
            radius = (bearingImage.rows / 2.0f - i)
                    * (bearingImage.rows / 2.0f - i)
                    / (image.rows / 2.0f - indentTop)
                    / (image.rows / 2.0f - indentTop)

                    + (bearingImage.cols / 2.0f - j)
                    * (bearingImage.cols / 2.0f - j)
                    / (image.cols / 2.0f - indentRight)
                    / (image.cols / 2.0f - indentRight);
            if (radius < 1.0f)
            {
                outputImage.at<Vec3b>(i - max_KernelSize, j - max_KernelSize) =
                    bearingImage.at<Vec3b>(i, j);
                continue;
            }
            else
            {
                sumB = sumG = sumR = 0;
                size = (int)(5.0f * radius + 0.5f);
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
                outputImage.at<Vec3b>(i - max_KernelSize, j - max_KernelSize) = Color;
            }
        }
    }

    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
    imwrite("/home/dmitry/Images/lena0.jpeg", outputImage, compression_params);

	outputImage.convertTo(dst, CV_8UC3);
	return 0;
}
