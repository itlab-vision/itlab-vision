#include <opencv2/core/core.hpp>
#include <opencv2/core/internal.hpp>
#include "photoeffects.hpp"

using namespace cv;

namespace
{

class edgeBlurInvoker
{
    public:

    edgeBlurInvoker(const Mat& src, 
                    const Mat& imgBoxFilt, 
                    const Mat& mask, Mat& dst, 
                    int indentTop, 
                    int indentLeft)
    :   src_(src),
        dst_(dst),
        imgBoxFilt_(imgBoxFilt),
        mask_(mask),
        cols_(src.cols),
        indentTop_(indentTop),
        indentLeft_(indentLeft) {}

    void operator()(const BlockedRange& rowsRange) const
    {
        Mat srcStripe = src_.rowRange(rowsRange.begin(), rowsRange.end());
        Mat boxStripe = imgBoxFilt_.rowRange(rowsRange.begin(), 
                                            rowsRange.end());
        Mat dstStripe = dst_.rowRange(rowsRange.begin(), rowsRange.end());
        Mat maskStripe = mask_.rowRange(rowsRange.begin(), rowsRange.end());

        int rows = srcStripe.rows;
        for (int i = 0; i < rows; i++)
        {
            uchar* row = (uchar*)srcStripe.row(i).data;
            uchar* boxRow = (uchar*)boxStripe.row(i).data;
            uchar* dstRow = (uchar*)dstStripe.row(i).data;
            float* maskRow = (float*)maskStripe.row(i).data;

            for (int j = 0; j < 3 * cols_; j += 3)
            {
                dstRow[j] = boxRow[j] * maskRow[j / 3] 
                            + row[j] * (1.0f - maskRow[j / 3]);
                dstRow[j + 1] = boxRow[j + 1] * maskRow[j / 3] 
                                + row[j + 1] * (1.0f - maskRow[j / 3]);
                dstRow[j + 2] = boxRow[j + 2] * maskRow[j / 3]
                                + row[j + 2] * (1.0f - maskRow[j / 3]);
            }
        }
    }

private:
    const Mat& src_;
    const Mat& imgBoxFilt_;
    const Mat& mask_;
    Mat& dst_;
    int indentTop_;
    int indentLeft_;
    int cols_;

    edgeBlurInvoker& operator=(const edgeBlurInvoker&);
};

}

int edgeBlur(InputArray src, OutputArray dst, int indentTop, int indentLeft)
{
    CV_Assert(!src.empty());
    CV_Assert(src.type() == CV_8UC3);
    dst.create(src.size(), src.type());
    Mat image = src.getMat(), outputImage = dst.getMat();
    
    CV_Assert(indentTop >= 0 && indentTop <= (image.rows / 2 - 10));
    CV_Assert(indentLeft >= 0 && indentLeft <= (image.cols / 2 - 10));

    float halfWidth = image.cols / 2.0f;
    float halfHeight = image.rows / 2.0f;
    float a = (halfWidth - indentLeft) * (halfWidth - indentLeft);
    float b = (halfHeight - indentTop) * (halfHeight - indentTop);
    float length = halfWidth * halfWidth / a 
                + halfHeight * halfHeight / b - 1.0f;
    Mat mask = Mat::zeros(image.size(), CV_32FC1);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            float magn = 
                (halfWidth - i) * (halfWidth - i) / a + 
                (halfHeight - i) * (halfHeight - i) / b - 1.0f;
            if (magn > 0.0f)
            {   
                mask.at<float>(i,j) = magn / length;
            }
        }
    }

    int kSize = MAX(image.rows, image.cols) / 100;
    Mat imgBoxFilt(image.size(), CV_8UC3);
    boxFilter(image, imgBoxFilt, -1, 
            Size(kSize, kSize), Point(-1, -1), 
            true, BORDER_REPLICATE);

    parallel_for(BlockedRange(0, image.rows), 
        edgeBlurInvoker(image, 
                        imgBoxFilt, 
                        mask, 
                        outputImage, 
                        indentTop, 
                        indentLeft));
    return 0;
}