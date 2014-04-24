#include <opencv2/core/core.hpp>
#include <opencv2/core/internal.hpp>
#include "photoeffects.hpp"
#include <iostream>
using namespace cv;
using namespace std;
class FilmGrainInvoker
{
public:
    FilmGrainInvoker(const Mat& src, Mat& dst, int grainValue)
        : src_(src),
          dst_(dst),
          grainValue_(grainValue),
          height_(src.cols) {}

    void operator()(const BlockedRange& rows) const
    {
        Mat srcStripe = src_.rowRange(rows.begin(), rows.end());
        cvtColor(srcStripe, srcStripe, CV_RGB2YUV);
        int stripeWidht = srcStripe.rows;
        RNG& rng=theRNG();
        for (int y = 0; y < stripeWidht; y++)
        {
            uchar* row = (uchar*)srcStripe.row(y).data;
            for (int x = 0; x < height_*3; x+=3)
            {
                int newValue=(row[x]+rng(grainValue_));
                if(newValue<0)
                {
                    newValue=0;
                }
                if(newValue>=256)
                {
                    newValue=255;
                }
                row[x]= newValue;
            }
        }
        Mat dstStripe = dst_.rowRange(rows.begin(), rows.end());
        cvtColor(srcStripe, dstStripe, CV_YUV2RGB);
    }

private:
    const Mat& src_;
    Mat& dst_;
    int grainValue_;
    int height_;

    FilmGrainInvoker& operator=(const FilmGrainInvoker&);
};
int filmGrain(InputArray src, OutputArray dst, int grainValue)
{
    CV_Assert(!src.empty());
    CV_Assert(src.type() == CV_8UC1 || src.type() == CV_8UC3);

    Mat image=src.getMat();

    RNG& rng=theRNG();
    if(src.type()==CV_8UC1)
    {
        for(int i=0; i<image.rows; i++)
            for(int j=0; j<image.cols; j++)
            {
                int newValue=(image.at<uchar>(i, j)+rng.gaussian(grainValue));
                if(newValue<0)
                {
                    newValue=0;
                }
                if(newValue>=256)
                {
                    newValue=255;
                }
                image.at<uchar>(i, j)= newValue;
            }
        image.copyTo(dst);
    }
    if(src.type()==CV_8UC3)
    {
        dst.create(image.size(), image.type());
        Mat dstMat = dst.getMat();
        cout<<getNumThreads()<<endl;
        setNumThreads(2);
        cout<<getNumThreads()<<endl;
        parallel_for(BlockedRange(0, image.rows), FilmGrainInvoker(image, dstMat, grainValue));
    }
    return 0;

}
