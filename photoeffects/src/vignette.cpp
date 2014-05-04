#include "photoeffects.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/core/internal.hpp>

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

class VignetteCalculate
{
private:
    const Mat& imgSrc;
    Mat& imgDst;
    float centerRow, centerCol, aSquare, bSquare, ab, radiusMax;

    VignetteCalculate& operator=(const VignetteCalculate&);

public:
    VignetteCalculate(Mat src, Mat dst, Size rect):
        imgSrc(src),
        imgDst(dst)
    {
        centerRow = imgSrc.rows / 2.0f;
        centerCol = imgSrc.cols / 2.0f;
        aSquare = rect.height * rect.height / 4.0f;
        bSquare = rect.width * rect.width / 4.0f;
        ab = rect.height * rect.width / 4.0f;
        radiusMax = sqrtf(centerRow * centerRow + centerCol * centerCol);
    }

    void operator()(const BlockedRange& rows) const
    {
        for (int i = rows.begin(); i != rows.end(); i++)
        {
            float iMinusCenterRow = (i - centerRow);
            float iMinusCenterRowSquare = iMinusCenterRow * iMinusCenterRow;

            for (int j = 0; j < imgSrc.cols; j++)
            {
                Vec3b intensity = imgSrc.at<Vec3b>(i, j);

                float jMinusCenterColSquare = (j - centerCol) * (j - centerCol);
                Vec3b intensityNew = intensity;
                if (iMinusCenterRowSquare / aSquare + jMinusCenterColSquare / bSquare > 1.0f)
                {
                    float dist = sqrtf(iMinusCenterRowSquare + jMinusCenterColSquare);
                    float sinFi = iMinusCenterRow / dist;
                    float sinFiSquare = sinFi * sinFi;
                    float radiusEllipse = ab / sqrtf(aSquare * (1.0f - sinFiSquare) +
                                              bSquare * sinFiSquare);
                    float coefficient = 1.0f - ((dist - radiusEllipse) /
                                          (radiusMax - radiusEllipse));

                    intensityNew *= coefficient;
                }
                imgDst.at<Vec3b>(i, j) = intensityNew;
            }
        }
    }
};

int vignette(InputArray src, OutputArray dst, Size rect)
{
    TIMER_START(Other);
    CV_Assert(src.type() == CV_8UC3 && rect.height != 0 && rect.width != 0);

    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);

    dst.create(imgSrc.size(), CV_8UC3);
    Mat imgDst = dst.getMat();
    TIMER_END(Other);

    TIMER_START(Main);
    parallel_for(BlockedRange(0, imgSrc.rows), VignetteCalculate(imgSrc, imgDst, rect));
    TIMER_END(Main);
    return 0;
}
