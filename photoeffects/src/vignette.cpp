#include "photoeffects.hpp"

using namespace cv;

int vignette(InputArray src, OutputArray dst, Size rect)
{
    CV_Assert(src.type() == CV_8UC3 && rect.height != 0 && rect.width != 0);

    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);

    dst.create(imgSrc.size(), CV_8UC3);
    Mat imgDst = dst.getMat();

    float centerRow = imgSrc.rows / 2.0f;
    float centerCol = imgSrc.cols / 2.0f;
    float aSquare = rect.height * rect.height / 4.0f;
    float bSquare = rect.width * rect.width / 4.0f;
    float radiusMax = centerRow * centerRow / aSquare + centerCol * centerCol / bSquare - 1;

    for (int i = 0; i < imgSrc.rows; i++)
    {
        for (int j = 0; j < imgSrc.cols; j++)
        {
            Vec3b intensity = imgSrc.at<Vec3b>(i, j);

            float dist = (i - centerRow) * (i - centerRow) / aSquare +
                    (j - centerCol) * (j - centerCol) / bSquare;
            if (dist > 1.0f)
            {
                float coefficient = 1.0f - (dist - 1.0f) / radiusMax;
                intensity *= coefficient;
            }
            imgDst.at<Vec3b>(i, j) = intensity;
        }
    }
    return 0;
}
