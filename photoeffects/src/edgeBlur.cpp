#include "photoeffects.hpp"

using namespace cv;

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    CV_Assert(!src.empty());
    CV_Assert(src.type() == CV_8UC3);
    dst.create(src.size(), src.type());
    Mat image = src.getMat(), outputImage = dst.getMat();
    
    CV_Assert(indentTop >= 0 && indentTop <= (image.rows / 2 - 10));
    CV_Assert(indentLeft >= 0 && indentLeft <= (image.cols / 2 - 10));

    Mat x(image.rows, image.cols, CV_32FC1);
    Mat y(image.rows, image.cols, CV_32FC1);
    Mat magn;

    float a = image.rows / 2 - indentTop;
    float b = image.cols / 2 - indentLeft;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            x.at<float>(i,j) = (i - image.rows / 2.0f) / a;
            y.at<float>(i,j) = (j - image.cols / 2.0f) / b;
        }
    }
    cartToPolar(x, y, magn, angle, true);

    int kSize = MAX(image.rows, image.cols) / 50;
    Mat imgBoxFilter(image.size(), CV_8UC3);
    boxFilter(image, imgBoxFilter, -1, 
            Size(kSize, kSize), Point(-1, -1), 
            true, BORDER_REPLICATE);

    Mat mask = Mat::zeros(image.size(), CV_8UC3);
    float length = magn.at<float>(0, 0) - 1.0f;
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            if (magn.at<float>(i,j) > 1.0f)
            {
                mask.at<Vec3b>(i,j) =
                    Vec3b::all((magn.at<float>(i,j) - 1.0f) * 100.0f / length);
            }
        }
    }

    Mat negMask(image.size(), CV_8UC3, Scalar(100, 100, 100));
    negMask -= mask;
    outputImage = imgBoxFilter.mul(mask, 0.01f) + image.mul(negMask, 0.01f);
    return 0;
}