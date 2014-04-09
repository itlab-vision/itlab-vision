#include <gtest/gtest.h>

#include "photoeffects.hpp"

using namespace cv;

namespace
{
    int suppressAssertionMessage(int, const char *, const char *,
                                const char *, int, void *)
    {}
}

TEST(photoeffects, SepiaInvalidImageFormat)
{
    Mat src(10, 10, CV_8UC3);
    Mat dst;

    // program should not stop if assertion fails
    setBreakOnError(false);
    // don't show message on assertion failure
    redirectError(suppressAssertionMessage);
    int errorCode = 0;
    // try to catch an exception thrown by CV_Assert
    try
    {
        sepia(src, dst);
    }
    catch (Exception & e)
    {
        errorCode = e.code;
    }
    // check if assertion has been failed
    EXPECT_EQ(CV_StsAssert, errorCode);
}


TEST(photoeffects, SepiaTest)
{
    Mat src(10, 10, CV_8UC1, Scalar(0)), dst, hsvDst;
    vector<Mat> channels(3);

    EXPECT_EQ(0, sepia(src, dst));
    cvtColor(dst, hsvDst, CV_BGR2HSV);
    split(hsvDst, channels);
    EXPECT_LE(19 - 1, channels[0].at<uchar>(0, 0)); // hue = 19
    EXPECT_GE(19 + 1, channels[0].at<uchar>(0, 0));
    EXPECT_LE(78 - 1, channels[1].at<uchar>(0, 0)); // saturation = 78
    EXPECT_GE(78 + 1, channels[1].at<uchar>(0, 0));
    EXPECT_LE(src.at<uchar>(0, 0) + 20 - 1, channels[2].at<uchar>(0, 0));
    EXPECT_GE(src.at<uchar>(0, 0) + 20 + 1, channels[2].at<uchar>(0, 0));
}

