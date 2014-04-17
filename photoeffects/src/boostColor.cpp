#include <opencv2/core/core.hpp>
#include <opencv2/core/internal.hpp>
#include "photoeffects.hpp"

using namespace cv;

namespace
{
class BoostColorInvoker
{
public:
    BoostColorInvoker(const Mat& src, Mat& dst, float intensity)
        : src_(src),
          dst_(dst),
          intensity_(intensity),
          height_(src.cols) {}

    void operator()(const BlockedRange& rows) const
    {
        Mat srcStripe = src_.rowRange(rows.begin(), rows.end());
        srcStripe /= 255.0f;
        cvtColor(srcStripe, srcStripe, CV_BGR2HLS);
        int stripeWidht = srcStripe.rows;
        for (int y = 0; y < stripeWidht; y++)
        {
            float* row = (float*)srcStripe.row(y).data;
            for (int x = 0; x < height_*3; x += 3)
            {
                row[x + 2] = min(row[x + 2] + intensity_, 1.0f);
            }
        }
        Mat dstStripe = dst_.rowRange(rows.begin(), rows.end());
        cvtColor(srcStripe, dstStripe, CV_HLS2BGR);
        dstStripe *= 255.0f;
    }

private:
    const Mat& src_;
    Mat& dst_;
    float intensity_;
    const int height_;

    BoostColorInvoker& operator=(const BoostColorInvoker&);
};
}

int boostColor(InputArray src, OutputArray dst, float intensity)
{
    Mat srcImg = src.getMat();

    CV_Assert(srcImg.channels() == 3);
    CV_Assert(intensity >= 0.0f && intensity <= 1.0f);

    int srcImgType = srcImg.type();
    if (srcImgType != CV_32FC3)
    {
        srcImg.convertTo(srcImg, CV_32FC3);
    }

    dst.create(srcImg.size(), srcImg.type());
    Mat dstMat = dst.getMat();
    parallel_for(BlockedRange(0, srcImg.rows), BoostColorInvoker(srcImg, dstMat, intensity));
    dstMat.convertTo(dst, srcImgType);

    return 0;
}
