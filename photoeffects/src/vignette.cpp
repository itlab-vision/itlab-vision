#include "photoeffects.hpp"

#if 1
    #include <stdio.h>
    #define TIMER_START(name) int64 t_##name = getTickCount()
    #define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
                1000.f * ((getTickCount() - t_##name) / getTickFrequency()))
#else
    #define TIMER_START(name)
    #define TIMER_END(name)
#endif

using namespace cv;

int vignette(InputArray src, OutputArray dst, Size rect)
{
    TIMER_START(Initialize);
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
    TIMER_END(Initialize);

    TIMER_START(Main);
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
    TIMER_END(Main);
    return 0;
}
