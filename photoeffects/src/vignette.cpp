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
    float centerRow, centerCol, aSquare, bSquare, radiusMax;

    VignetteCalculate& operator=(const VignetteCalculate&);

public:
    VignetteCalculate(Mat src, Mat dst, Size rect):
        imgSrc(src),
        imgDst(dst)
    {
        float centerRow = imgSrc.rows / 2.0f;
		float centerCol = imgSrc.cols / 2.0f;
		float aSquare = rect.height * rect.height / 4.0f;
		float bSquare = rect.width * rect.width / 4.0f;
		float radiusMax = centerRow * centerRow / aSquare + centerCol * centerCol / bSquare - 1;
    }

    void operator()(const BlockedRange& iters) const
    {
    	for (int i = iters.begin(); i != iters.end(); i++)
    	{
    		Vec3b intensity = imgSrc.at<Vec3b>(i);

    		float dist = ((int)(i / imgSrc.cols) - centerRow) * ((int)(i / imgSrc.cols) - centerRow) / aSquare +
	                    ((int)(i / imgSrc.rows) - centerCol) * ((int)(i / imgSrc.rows) - centerCol) / bSquare;
            if (dist > 1.0f)
            {
                float coefficient = 1.0f - (dist - 1.0f) / radiusMax;
                intensity *= coefficient;
            }
            imgDst.at<Vec3b>(i) = intensity;
    	}
    }

    /*void operator()(const BlockedRange& rows) const
    {
        for (int i = rows.begin(); i != rows.end(); i++)
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
    }*/
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
    parallel_for(BlockedRange(0, imgSrc.rows * imgSrc.cols), VignetteCalculate(imgSrc, imgDst, rect));
    TIMER_END(Main);
    return 0;
}
