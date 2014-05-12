#include "photoeffects.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/core/internal.hpp>

using namespace cv;

class VignetteInvoker
{
private:
    const Mat& imgSrc;
    Mat& imgDst;
    float centerRow, centerCol, aSquare, bSquare, radiusMax;

    VignetteInvoker& operator=(const VignetteInvoker&);

public:
    VignetteInvoker(const Mat& src, Mat& dst, Size rect):
        imgSrc(src),
        imgDst(dst)
    {
        centerRow = imgSrc.rows / 2.0f;
		centerCol = imgSrc.cols / 2.0f;
		aSquare = rect.height * rect.height / 4.0f;
		bSquare = rect.width * rect.width / 4.0f;
		radiusMax = centerRow * centerRow / aSquare + centerCol * centerCol / bSquare - 1.0f;
    }

    void operator()(const BlockedRange& rows) const
    {
    	Mat srcStripe = imgSrc.rowRange(rows.begin(), rows.end());
    	Mat dstStripe = imgDst.rowRange(rows.begin(), rows.end());
    	srcStripe.copyTo(dstStripe);
    	int stripeWidth = srcStripe.rows;

        for (int i = rows.begin(); i < rows.end(); i++)
        {
        	Vec3b* srcRow = (Vec3b*)srcStripe.row(i - rows.begin()).data;
        	Vec3b* dstRow = (Vec3b*)dstStripe.row(i - rows.begin()).data;
            for (int j = 0; j < imgSrc.cols; j++)
	        {
	            float dist = (i - centerRow) * (i - centerRow) / aSquare +
	                    (j - centerCol) * (j - centerCol) / bSquare;
	            float coefficient = 1.0f;
	            if (dist > 1.0f)
	            {
	                coefficient = 1.0f - (dist - 1.0f) / radiusMax;
	            }
	            dstRow[j] *= coefficient;
	        }
        }
    }
};

int vignette(InputArray src, OutputArray dst, Size rect)
{
    CV_Assert(src.type() == CV_8UC3 && rect.height != 0 && rect.width != 0);

    Mat imgSrc = src.getMat();
    CV_Assert(imgSrc.data);

    dst.create(imgSrc.size(), CV_8UC3);
    Mat imgDst = dst.getMat();

    parallel_for(BlockedRange(0, imgSrc.rows), VignetteInvoker(imgSrc, imgDst, rect));
    return 0;
}