#include "photoeffects.hpp"
#include <math.h>

using namespace cv;

#define MAX_KERNELSIZE 15

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    CV_Assert(src.type() == CV_8UC3);
    dst.create(src.size(), src.type());
    Mat image = src.getMat(), outputImage = dst.getMat();
    
    CV_Assert(indentTop >= 0 && indentTop <= (image.rows / 2 - 10));
    CV_Assert(indentLeft >= 0 && indentLeft <= (image.cols / 2 - 10));

    float halfWidth = (image.cols / 2.0f) * (image.cols / 2.0f);
    float halfHeight = (image.rows / 2.0f) * (image.rows / 2.0f);
    float a = (image.cols / 2.0f - indentLeft) 
            * (image.cols / 2.0f - indentLeft);
    float b = (image.rows / 2.0f - indentTop) 
            * (image.rows / 2.0f - indentTop);
    int kSizeEdges = halfWidth / a + halfHeight / b;

    kSizeEdges = MIN(kSizeEdges, MAX_KERNELSIZE);
    Mat bearingImage(image.rows + 2 * kSizeEdges,
                    image.cols + 2 * kSizeEdges,
                    CV_8UC3);
    copyMakeBorder(image, bearingImage, kSizeEdges, kSizeEdges,
        kSizeEdges, kSizeEdges, BORDER_REPLICATE);


    for (int i = kSizeEdges; i < bearingImage.rows - kSizeEdges; i++)
    {
        for (int j = kSizeEdges; j < bearingImage.cols - kSizeEdges; j++)
        {
            int size;
            Vec3f sumF;
            Vec3b Color;
            float sumC = 0.0f, coeff;
            float bearHalfWidth = bearingImage.cols / 2.0f;
            float bearHalfHeight = bearingImage.rows / 2.0f;
            float radius = (bearHalfHeight - i)
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
            size = radius;
            radius = 2.0f * (radius - 0.5f) * (radius - 0.5f);
            size = MIN(size, kSizeEdges);
            for (int x = -size; x <= size; x++)
            {
                for (int y = -size; y <= size; y++)
                {
                    coeff = 1.0f / (CV_PI * radius)
                            * exp(- (x * x + y * y) / radius);

                    Color = bearingImage.at<Vec3b>(x + i, y + j);
                    sumF += (Vec3f) (coeff * Color);
                    sumC += coeff;
                }
            }
            sumF *= (1.0f / sumC);
            outputImage.at<Vec3b>(i - kSizeEdges, j - kSizeEdges) = sumF;
        }
    }

    return 0;
}
