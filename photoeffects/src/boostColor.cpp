#include "photoeffects.hpp"

const int MAX_INTENSITY = 255; 

using namespace cv;

int boostColor(cv::InputArray src, cv::OutputArray dst, float intensity)
{
    Mat srcImg = src.getMat();

    CV_Assert(srcImg.channels() == 3);
    CV_Assert(intensity >= 0.0f && intensity <= 1.0f);

    if (srcImg.type() != CV_8UC3)
    {
        srcImg.convertTo(srcImg, CV_8UC3);
    }

    Mat srcHls;
    cvtColor(srcImg, srcHls, CV_BGR2HLS);

	int intensityInt = intensity * MAX_INTENSITY;
    for (int y = 0; y < srcHls.rows; y++)
    {
        unsigned char* row = srcHls.row(y).data;
        for (int x = 0; x < srcHls.cols*3; x += 3)
        {
            row[x + 2] = min(row[x + 2] + intensityInt, MAX_INTENSITY);
        }
    }
	
    cvtColor(srcHls, dst, CV_HLS2BGR);
	dst.getMat().convertTo(dst, srcImg.type());

    return 0;
}