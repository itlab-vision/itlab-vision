#include "photoeffects.hpp"

    #include <stdio.h>
    #define TIMER_START(name) int64 t_##name = getTickCount()
    #define TIMER_END(name) printf("TIMER_" #name ":\t%6.2fms\n", \
                1000.f * ((getTickCount() - t_##name) / getTickFrequency()))

using namespace cv;

int boostColor(cv::InputArray src, cv::OutputArray dst, float intensity)
{
    const int MAX_INTENSITY = 255;

    Mat srcImg = src.getMat();

    CV_Assert(srcImg.channels() == 3);
    CV_Assert(intensity >= 0.0f && intensity <= 1.0f);

    if (srcImg.type() != CV_8UC3)
    {
        srcImg.convertTo(srcImg, CV_8UC3);
    }

    Mat srcHls;
	TIMER_START(toHls);
    cvtColor(srcImg, srcHls, CV_BGR2HLS);
	TIMER_END(toHls);
    int intensityInt = intensity * MAX_INTENSITY;
    srcHls += Scalar(0, 0, intensityInt);
	TIMER_START(toBGR);
    cvtColor(srcHls, dst, CV_HLS2BGR);
	TIMER_END(toBGR);
    dst.getMat().convertTo(dst, srcImg.type());
	imwrite("result.jpg", dst.getMat());
    return 0;
}